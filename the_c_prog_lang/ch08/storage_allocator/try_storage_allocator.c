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


typedef struct {
    double coord[3];
} pure_coords;

// Another struct with 32 bytes that matches Header
// Might use this one for some other tests
typedef struct {
    double time;
    double coord[3];
} time_coords;


void fill_coords(pure_coords * arr, size_t sz) {
    for (int i = 0; i < sz; ++i) {
        for (int j = 0; j < 3; ++j) {
            const double new_coord = rand() * 1.0 / RAND_MAX;
            printf("New coord = %f\n", new_coord);
            arr[i].coord[j] = new_coord;
        }
    }
}


#define MAX_NUM_BLOCKS 6


typedef enum {
    ALOC,
    FR
} mem_op;

typedef union {
    size_t size; // Used for alloc
    size_t index; // Used for free
} mem_val;

typedef struct {
    mem_op op;
    mem_val val;
} test_data;

#define TD_ALLOC(sz) ((test_data){ .op = ALOC, .val.size = (sz) })
#define TD_FREE(idx) ((test_data){ .op = FR, .val.index = (idx) })

void copy_coords(const pure_coords * src, pure_coords * dst, size_t size_to_cpy) {
    for (size_t i = 0; i < size_to_cpy; ++i) {
        for (int j = 0; j < 3; ++j) {
            dst[i].coord[j] = src[i].coord[j];
        }
    }
}

void test_hole_in_mem(void) {
    printf("\n\n test_hole_in_mem\n");
    printf("\n\n Sizeof(pure_coords) = %zu\n", sizeof(pure_coords));
    printf("\n\n Sizeof(time_coords) = %zu\n", sizeof(time_coords));
    
    pure_coords coords_arr[MAX_NUM_BLOCKS];
    fill_coords(coords_arr, MAX_NUM_BLOCKS);

    test_data test_arr[] = {
        TD_ALLOC(1),
        TD_ALLOC(2),
        TD_FREE(0),
        TD_ALLOC(3)
    };

    pure_coords * malloc_coords_arr[MAX_NUM_BLOCKS] = {NULL};

    size_t index = 0;
    for (int i = 0; i < sizeof(test_arr)/sizeof(test_arr[0]); ++i) {
        switch (test_arr[i].op) {
            case ALOC:
            {
                pure_coords * malloc_coords = MALLOC(test_arr[i].val.size * sizeof(pure_coords));
                malloc_coords_arr[index] = malloc_coords;
                index++;
                copy_coords(coords_arr, malloc_coords, test_arr[i].val.size);
                break;
            }
            case FR:
            {
                if (test_arr[i].val.index < MAX_NUM_BLOCKS) {
                    FREE(malloc_coords_arr[test_arr[i].val.index]);
                    malloc_coords_arr[test_arr[i].val.index] = NULL;
                } else {
                    printf("ERROR: Free index = %zu is out of bounds\n", test_arr[i].val.index);
                }
                break;
            }
            default:
            {
                printf("ERROR: Allocation test case not known. Case value = %d\n", test_arr[i].op);
                break;
            }
        }
    }

    print_cases();

    // for (int iteration = 0; iteration < MAX_NUM_BLOCKS; ++iteration) {
    //     // int coords_sz = iteration + 1;
    //     int coords_sz = MAX_NUM_BLOCKS - iteration;
    //     pure_coords * malloc_coords = MALLOC(coords_sz * sizeof(pure_coords));

    //     for (size_t i = 0; i < coords_sz; ++i) {
    //         for (int j = 0; j < 3; ++j) {
    //             malloc_coords[i].coord[j] = coords_arr[i].coord[j];
    //         }
    //     }

    //     // printf("Malloc array\n");

    //     // for (size_t i = 0; i < coords_sz; ++i) {
    //     //     for (int j = 0; j < 3; ++j) {
    //     //         printf("Malloc coord = %f\n", malloc_coords[i].coord[j]);
    //     //     }
    //     // }
    //     malloc_coords_arr[iteration] = malloc_coords;
    // }

    // printf("After all mallocs\n");
    // print_mem_blocks();

    // for (int iteration = 0; iteration < MAX_NUM_BLOCKS; ++iteration) {
    // for (int iteration = MAX_NUM_BLOCKS - 1; iteration >= 0; --iteration) {
    //     // Free everything
    //     // FREE(malloc_coords_arr[iteration]);
    //     // printf("\nAfter free iteration %d\n", iteration);
    //     // print_mem_blocks();

    //     // Free even blocks
    //     // if (iteration % 2 == 0) {
    //     //     FREE(malloc_coords_arr[iteration]);
    //     //     printf("\nAfter free iteration %d\n", iteration);
    //     //     print_mem_blocks();
    //     // }
        
    //     // Free odd block
    //     if (iteration % 2 != 0) {
    //         FREE(malloc_coords_arr[iteration]);
    //         printf("\nAfter free iteration %d\n", iteration);
    //         print_mem_blocks();
    //     }
        
    //     // Free every 3rd
    //     // if (iteration % 3 == 0) {
    //     //     FREE(malloc_coords_arr[iteration]);
    //     //     printf("\nAfter free iteration %d\n", iteration);
    //     //     print_mem_blocks();
    //     // }
    // }
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

    // test_single_malloc_free();

    // print_mem_blocks();

    // test_single_malloc_free();

    // test_multiple_malloc_free();

    // print_mem_blocks();

    test_hole_in_mem();

    return 0;
}
