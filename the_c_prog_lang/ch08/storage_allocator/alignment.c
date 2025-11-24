/*
While working on storage allocator memory alignment of types came up. This code is some experiments
to understand the alignment of types.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <stddef.h>
#include <stdint.h>

typedef struct example {
  char c;
  int i;
  double d;
} example;

typedef struct example1 {
  char c1; 
  int i1;
  char c2;  
  double d1;
  char c3;
  double d2;
  char c4;
  int i2;
} example1;

typedef struct example2 {
  char c1; 
  char c2;
  char c3;
  char c4;
  int i1;
  int i2;
  double d1;
  double d2;
} example2;


void pause_for_input(const char * msg) {
    // printf("Pausing %s\n", msg);
    printf("%s Program break: %p\n", msg, sbrk(0));
    // printf("Now enter a number to continue\n");
    // int num = 0;
    // scanf("%d", &num);
    // printf("Number is %d ... continuing\n", num);
}


#include <string.h>

#define MAXLINE 256


const char *region_of(void *addr) {
    static char line[MAXLINE];
    static char region[MAXLINE];
    unsigned long start, end;
    FILE *f = fopen("/proc/self/maps", "r");
    if (!f) return "unknown";

    while (fgets(line, sizeof(line), f)) {
        if (sscanf(line, "%lx-%lx", &start, &end) == 2) {
            if ((unsigned long)addr >= start && (unsigned long)addr < end) {
                // extract region name (file or [heap]/[stack]/etc.)
                char *name = strchr(line, '/');
                if (!name) name = strchr(line, '[');
                if (name) {
                    name[strcspn(name, "\n")] = 0; // strip newline
                    snprintf(region, sizeof(region), "%s", name);
                } else {
                    snprintf(region, sizeof(region), "anonymous");
                }
                fclose(f);
                return region;
            }
        }
    }
    fclose(f);
    return "not found";
}

void show_address(const char *label, void *ptr) {
    printf("%-10s %p  →  %s\n", label, ptr, region_of(ptr));
}


void experiment_sizeof(void) {
    printf("Size of (bytes):\n");
    printf("  char        : %zu\n", sizeof(char));
    printf("  int         : %zu\n", sizeof(int));
    printf("  long        : %zu\n", sizeof(long));
    printf("  double      : %zu\n", sizeof(double));
    printf("  max_align_t : %zu\n", sizeof(max_align_t));
    printf("  example     : %zu\n", sizeof(example));
    printf("  example1    : %zu\n", sizeof(example1));
    printf("  example2    : %zu // This has smaller size than example1!!\n", sizeof(example2));
    puts("");
}


void experiment_alignment(void) {
    printf("Alignment requirements (bytes):\n");
    printf("  char        : %zu\n", _Alignof(char));
    printf("  int         : %zu\n", _Alignof(int));
    printf("  long        : %zu\n", _Alignof(long));
    printf("  double      : %zu\n", _Alignof(double));
    printf("  max_align_t : %zu\n", _Alignof(max_align_t));
    printf("  example     : %zu\n", _Alignof(example));
    printf("  example1    : %zu\n", _Alignof(example1));
    printf("  example2    : %zu\n", _Alignof(example2));
    puts("");
}


void experiment_offset(void) {
    printf("Offset of example struct:\n");
    
    printf("example struct member offset (bytes):\n");
    printf("  offsetof(c) : %zu // It starts here\n", offsetof(example, c));
    printf("  offsetof(i) : %zu // There is a padding of 3 bytes after char\n",
           offsetof(example, i));
    printf("  offsetof(d) : %zu // No padding needed here\n", offsetof(example, d));
    puts("");

    example ex;
    void *c_p = (void*)&(ex.c);
    void *i_p = (void*)&(ex.i);
    void *d_p = (void*)&(ex.d);
    
    printf("address of struct members:\n");
    printf("  &example.c : %p\n", c_p);
    printf("  &example.i : %p // Note the padding!\n", i_p);
    printf("  &example.d : %p\n", d_p);
    puts("");

    printf("calculated offset of struct members:\n");
    printf("  &offset.c : %zu\n", (c_p - c_p));
    printf("  &offset.i : %zu\n", (i_p - c_p));
    printf("  &offset.d : %zu\n", (d_p - c_p));
    puts("");
}


void check_alignment_of_stack_vars(void) {
    char c;
    int i;
    long l;
    double d;
    example s;

    printf("STack Variable addresses:\n");
    printf("  &c       = %p\n", (void*)&c);
    printf("  &i       = %p\n", (void*)&i);
    printf("  &l       = %p\n", (void*)&l);
    printf("  &d       = %p\n", (void*)&d);
    printf("  &s       = %p\n", (void*)&s);
    puts("");

    printf("Stack vars alignment check (addr %% align == 0):\n");
    printf("  char     : %d\n", ((uintptr_t)&c) % _Alignof(char) == 0);
    printf("  int      : %d\n", ((uintptr_t)&i) % _Alignof(int) == 0);
    printf("  long     : %d\n", ((uintptr_t)&l) % _Alignof(long) == 0);
    printf("  double   : %d\n", ((uintptr_t)&d) % _Alignof(double) == 0);
    printf("  example  : %d\n", ((uintptr_t)&s) % _Alignof(example) == 0);
    puts("");
}


void check_alignment_of_heap_vars(void) {
    char *pc   = malloc(sizeof(char));
    int *pi    = malloc(sizeof(int));
    long *pl   = malloc(sizeof(long));
    double *pd = malloc(sizeof(double));

    printf("Heap pointer addresses:\n");
    printf("  char*    = %p\n", (void*)pc);
    printf("  int*     = %p\n", (void*)pi);
    printf("  long*    = %p\n", (void*)pl);
    printf("  double*  = %p\n", (void*)pd);

    printf("\nHeap vars alignment check:\n");
    printf("  char     : %d\n", ((uintptr_t)pc) % _Alignof(char) == 0);
    printf("  int      : %d\n", ((uintptr_t)pi) % _Alignof(int) == 0);
    printf("  long     : %d\n", ((uintptr_t)pl) % _Alignof(long) == 0);
    printf("  double   : %d\n", ((uintptr_t)pd) % _Alignof(double) == 0);

    free(pc);
    free(pi);
    free(pl);
    free(pd);
}


int global_var = 42;
static int static_global_var = 84;


int main(int argc, char *argv[]) {
    printf("Running sizeof, alignment and memory location experiments\n");

    // Sequence
    // Start with sizeof and why example, example1 and example2 sizes are unexpected
    // Next understand alignment of some primitives
    // Also for stuff on stack, heap and program data
    // Finally explore malloc and sbrk

    experiment_sizeof();
    puts("");

    experiment_alignment();
    puts("");

    experiment_offset();
    puts("");

    check_alignment_of_stack_vars();
    puts("");

    check_alignment_of_heap_vars();
    puts("");
    

    static int static_local_var = 321;
    int local_var = 1234;
    int *heap_var = malloc(sizeof(int));
    *heap_var = 5678;

    show_address("function", (void *)main);
    show_address("global", &global_var);
    show_address("static global", &static_global_var);
    show_address("static local", &static_local_var);
    show_address("heap", heap_var);
    show_address("stack", &local_var);

    free(heap_var);

    pause_for_input("Before malloc");

    int * data = (int *)malloc(100 * sizeof(int));

    printf("Data ptr = %p\n", data);

    pause_for_input("After malloc");

    free(data);

    pause_for_input("After free");

    sbrk(1024*100);

    pause_for_input("After sbrk(64)");
    
    
    return 0;
}
