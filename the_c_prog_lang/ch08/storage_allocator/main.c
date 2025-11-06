#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <stddef.h>

typedef struct example {
  char c;
  int i;
  double d;
} example;


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

    printf("sizeof(example) = %zu\n", sizeof(example));
    printf("alignof(example) = %zu\n", _Alignof(example));
    printf("offsetof(c) = %zu\n", offsetof(example, c));
    printf("offsetof(i) = %zu\n", offsetof(example, i));
    printf("offsetof(d) = %zu\n", offsetof(example, d));

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