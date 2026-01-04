#include "simple_allocator.h"

#include <stdio.h>

#include <stdlib.h>
#include <time.h>

// Comment to try the new allocator
// #define DEBUG

#ifdef DEBUG
// For testing only
#define MALLOC malloc
#define FREE free

#else
#define MALLOC my_malloc
#define FREE my_free
#endif


void test_multiple_malloc_free() {
    printf("\n\nMultiple malloc free\n");
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
    printf("\n\nSingle malloc free\n");
    const char * hello_world = "Hello World";
    char *str = (char *)MALLOC(12);

    print_mem_blocks();

    for (int i = 0; i < 12; ++i) {
        str[i] = hello_world[i];
    }

    printf("Original str = %s\n", hello_world);
    printf("New str      = %s\n", str);

    FREE(str);
}


typedef struct double_vec {
    double coord[3];
} double_vec;


void fill_coords(double_vec * arr, size_t sz) {
    for (int i = 0; i < sz; ++i) {
        for (int j = 0; j < 3; ++j) {
            const double new_coord = rand() * 1.0 / RAND_MAX;
            printf("New coord = %f\n", new_coord);
            arr[i].coord[j] = new_coord;
        }
    }
}



int main() {
    printf("Running storage allocator\n");

    srand(time(NULL));

    double_vec coords_arr[10];
    fill_coords(coords_arr, 10);

    return 0;

    test_single_malloc_free();

    print_mem_blocks();

    test_single_malloc_free();

    test_multiple_malloc_free();

    print_mem_blocks();

    printf("\n\n Sizeof(double_vec) = %zu\n", sizeof(double_vec));

    return 0;
}
