#include "simple_allocator.h"

#include <stdio.h>

// Comment to try the new allocator
#define DEBUG

#ifdef DEBUG
// For testing only
#include <stdlib.h>

#define MALLOC malloc
#define FREE free

#else
#define MALLOC my_malloc
#define FREE my_free
#endif


int main() {
    printf("Running storage allocator\n");

    const char * hello_world = "Hello World";
    char *str = (char *)MALLOC(12);

    for (int i = 0; i < 12; ++i) {
        str[i] = hello_world[i];
    }

    printf("Original str = %s\n", hello_world);
    printf("New str      = %s\n", str);

    FREE(str);

    return 0;
}