#include "simple_allocator.h"

#include <stdio.h>

// Comment to try the new allocator
// #define DEBUG

#ifdef DEBUG
// For testing only
#include <stdlib.h>

#define MALLOC malloc
#define FREE free

#else
#define MALLOC my_malloc
#define FREE my_free
#endif


void test_multiple_malloc_free() {
    const char * orig_hello_world = "Hello World";
    char *my_hello_world = (char *)MALLOC(12);

    for (int i = 0; i < 12; ++i) {
        my_hello_world[i] = orig_hello_world[i];
    }

    printf("Original str = %s\n", orig_hello_world);
    printf("New str      = %s\n", my_hello_world);

    const char * orig_welcome_malloc = "Welcome My Malloc";
    char *my_welcome_malloc = (char *)MALLOC(18);

    for (int i = 0; i < 18; ++i) {
        my_welcome_malloc[i] = orig_welcome_malloc[i];
    }

    printf("Original str = %s\n", orig_welcome_malloc);
    printf("New str      = %s\n", my_welcome_malloc);

    FREE(my_hello_world);
    FREE(my_welcome_malloc);
}


void test_single_malloc_free() {
    const char * hello_world = "Hello World";
    char *str = (char *)MALLOC(12);

    for (int i = 0; i < 12; ++i) {
        str[i] = hello_world[i];
    }

    printf("Original str = %s\n", hello_world);
    printf("New str      = %s\n", str);

    FREE(str);
}


int main() {
    printf("Running storage allocator\n");

    test_single_malloc_free();

    test_single_malloc_free();

    // test_multiple_malloc_free();

    return 0;
}