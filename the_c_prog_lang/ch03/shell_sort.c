#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 100
#define NUM_TRIALS 10


void shell_sort(int arr[], int size) {
    for (int gap = size / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; ++i) {
            for (int j = (i - gap); j >= 0; j -= gap) {
                if (arr[j] > arr[j + gap]) {
                    int temp = arr[j];
                    arr[j] = arr[j + gap];
                    arr[j + gap] = temp;
                }
            }
        }
    }
}


void print_arr(int arr[], int size) {
    printf("[");
    for (int i = 0; i < size; ++i) {
        printf("%d", arr[i]);
        if (i < (size - 1)) {
            printf(", ");
        }
    }
    printf("]\n");
}


void fill_arr_with_random(int arr[], int size) {
    const int max_elem = 5 * size;
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % max_elem;
    }
}


bool is_arr_sorted(int arr[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}


int main() {
    bool debug = false;
    
    printf("Running tests for shell sort\n");

    srand(time(NULL));

    unsigned int num_failed = 0;
    for (int size = 1; size < MAX_SIZE; ++size) {
        int input_arr[MAX_SIZE] = {0};
        for (int trial = 0; trial < NUM_TRIALS; ++trial) {
            fill_arr_with_random(input_arr, size);
            
            if (debug) {
                printf("\nOriginal array of size = %d\n", size);
                print_arr(input_arr, size);
            }
            
            shell_sort(input_arr, size);
            
            if (debug) {
                printf("Sorted array of size = %d\n", size);
                print_arr(input_arr, size);
            }
            
            if (!is_arr_sorted(input_arr, size)) {
                printf("Failed to sort array of size = %d\n", size);
                print_arr(input_arr, size);
                ++num_failed;
            }
        }
    }
    
    if (num_failed > 0) {
        printf("%d test failed\n", num_failed);
    } else {
        printf("All tests passed\n");
    }
    printf("Done\n");

    return 0;
}
