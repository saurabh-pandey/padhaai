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
    printf("Pausing %s\n", msg);
    printf("%s Program break: %p\n", msg, sbrk(0));
    printf("Now enter a number to continue\n");
    int num = 0;
    scanf("%d", &num);
    printf("Number is %d ... continuing\n", num);
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

int global_var = 42;
static int static_global_var = 84;

void show_address(const char *label, void *ptr) {
    printf("%-10s %p  →  %s\n", label, ptr, region_of(ptr));
}


int main(int argc, char *argv[]) {
    printf("Running storage allocator\n");

    printf("Alignment of char        = %zu\n", _Alignof(char));
    printf("Alignment of int         = %zu\n", _Alignof(int));
    printf("Alignment of double      = %zu\n", _Alignof(double));
    printf("Alignment of example     = %zu\n", _Alignof(example));
    printf("Alignment of max_align_t = %zu\n", _Alignof(max_align_t));


    printf("sizeof(example) = %zu\n", sizeof(example));
    printf("alignof(example) = %zu\n", _Alignof(example));
    printf("offsetof(c) = %zu\n", offsetof(example, c));
    printf("offsetof(i) = %zu\n", offsetof(example, i));
    printf("offsetof(d) = %zu\n", offsetof(example, d));

    printf("sizeof(example1) = %zu\n", sizeof(example1));
    printf("alignof(example1) = %zu\n", _Alignof(example1));

    printf("sizeof(example2) = %zu\n", sizeof(example2));
    printf("alignof(example2) = %zu\n", _Alignof(example2));


    char c;
    int i;
    long l;
    double d;
    example s;

    printf("Alignment requirements (bytes):\n");
    printf("  char     : %zu\n", _Alignof(char));
    printf("  int      : %zu\n", _Alignof(int));
    printf("  long     : %zu\n", _Alignof(long));
    printf("  double   : %zu\n", _Alignof(double));
    printf("  example  : %zu\n", _Alignof(example));
    puts("");

    printf("Variable addresses:\n");
    printf("  &c       = %p\n", (void*)&c);
    printf("  &i       = %p\n", (void*)&i);
    printf("  &l       = %p\n", (void*)&l);
    printf("  &d       = %p\n", (void*)&d);
    printf("  &s       = %p\n", (void*)&s);
    puts("");

    printf("Alignment check (addr %% align == 0):\n");
    printf("  char     : %d\n", ((uintptr_t)&c) % _Alignof(char) == 0);
    printf("  int      : %d\n", ((uintptr_t)&i) % _Alignof(int) == 0);
    printf("  long     : %d\n", ((uintptr_t)&l) % _Alignof(long) == 0);
    printf("  double   : %d\n", ((uintptr_t)&d) % _Alignof(double) == 0);
    printf("  example  : %d\n", ((uintptr_t)&s) % _Alignof(example) == 0);


    char *pc   = malloc(sizeof(char));
    int *pi    = malloc(sizeof(int));
    long *pl   = malloc(sizeof(long));
    double *pd = malloc(sizeof(double));

    printf("Heap pointer addresses:\n");
    printf("  char*    = %p\n", (void*)pc);
    printf("  int*     = %p\n", (void*)pi);
    printf("  long*    = %p\n", (void*)pl);
    printf("  double*  = %p\n", (void*)pd);

    printf("\nAlignment check:\n");
    printf("  char     : %d\n", ((uintptr_t)pc) % _Alignof(char) == 0);
    printf("  int      : %d\n", ((uintptr_t)pi) % _Alignof(int) == 0);
    printf("  long     : %d\n", ((uintptr_t)pl) % _Alignof(long) == 0);
    printf("  double   : %d\n", ((uintptr_t)pd) % _Alignof(double) == 0);

    free(pc);
    free(pi);
    free(pl);
    free(pd);

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
