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


#define NUM_BLOCKS 4

void test_hole_in_mem(void) {
    printf("\n\n test_hole_in_mem\n");
    printf("\n\n Sizeof(double_vec) = %zu\n", sizeof(double_vec));
    
    double_vec coords_arr[NUM_BLOCKS];
    fill_coords(coords_arr, NUM_BLOCKS);

    double_vec * malloc_coords_arr[NUM_BLOCKS] = {NULL};

    for (int iteration = 0; iteration < NUM_BLOCKS; ++iteration) {
        int coords_sz = iteration + 1;
        double_vec * malloc_coords = MALLOC(coords_sz * sizeof(double_vec));

        for (size_t i = 0; i < coords_sz; ++i) {
            for (int j = 0; j < 3; ++j) {
                malloc_coords[i].coord[j] = coords_arr[i].coord[j];
            }
        }

        // printf("Malloc array\n");

        // for (size_t i = 0; i < coords_sz; ++i) {
        //     for (int j = 0; j < 3; ++j) {
        //         printf("Malloc coord = %f\n", malloc_coords[i].coord[j]);
        //     }
        // }
        malloc_coords_arr[iteration] = malloc_coords;
    }

    print_mem_blocks();

    for (int iteration = 0; iteration < NUM_BLOCKS; ++iteration) {
        // Free everything
        // FREE(malloc_coords_arr[iteration]);

        // Free even blocks
        if (iteration % 2 == 0) {
            FREE(malloc_coords_arr[iteration]);
        }
        
        // Free odd block
        // if (iteration % 2 != 0) {
        //     FREE(malloc_coords_arr[iteration]);
        // }
        
        // Free every 3rd
        // if (iteration % 3 == 0) {
        //     FREE(malloc_coords_arr[iteration]);
        // }
        printf("\nAfter iteration %d\n", iteration);
        print_mem_blocks();
    }
}


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

    // print_mem_blocks();

    for (int i = 0; i < 12; ++i) {
        str[i] = hello_world[i];
    }

    printf("Original str = %s\n", hello_world);
    printf("New str      = %s\n", str);

    FREE(str);
}


int main() {
    printf("Running storage allocator\n");

    srand(time(NULL));

    test_single_malloc_free();

    // print_mem_blocks();

    test_single_malloc_free();

    test_multiple_malloc_free();

    // print_mem_blocks();

    test_hole_in_mem();

    return 0;
}
