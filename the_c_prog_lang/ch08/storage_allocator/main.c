#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
    printf("Running storage allocator\n");

    void *brk = sbrk(0);
    printf("Before malloc Program break: %p\n", brk);

    int * data = (int *)malloc(1000000 * sizeof(int));

    brk = sbrk(0);
    printf("After malloc Program break : %p\n", brk);

    free(data);

    brk = sbrk(0);
    printf("After free Program break   : %p\n", brk);

    brk = sbrk(1024*100);
    printf("After calling sbrk(64)     : %p\n", sbrk(0));
    
    return 0;
}