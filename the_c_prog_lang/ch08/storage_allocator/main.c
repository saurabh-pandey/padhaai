#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <stddef.h>

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