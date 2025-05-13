#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define MAX_ARR_SZ 20
#define NUM_ITERATIONS 5
#define MIN_ARR_VAL -500
#define MAX_ARR_VAL 500

void fill_array(int input_arr[], int size, int iteration) {
    srand(time(NULL) + (NUM_ITERATIONS + 1) * size + iteration);

    for (int i = 0; i < size; ++i) {
        int val = MIN_ARR_VAL + (rand() % (MAX_ARR_VAL - MIN_ARR_VAL + 1));
        // printf("i = %d, Val = %d\n", i, val);
        input_arr[i] = val;
    }
}

void swap(int input_arr[], int left, int right) {
    const int temp = input_arr[left];
    input_arr[left] = input_arr[right];
    input_arr[right] = temp;
}

// NOTE: left and right args are assumed to be inclusive
void qsort_v1(int input_array[], int left, int right) {
    // Input array of size 1 or less is already sorted
    if (left >= right) {
        return;
    }

    // Input array is of size > 1
    const int pivot = (left + right) / 2;

    // Move pivot to the start of the array
    swap(input_array, left, pivot);

    // Partition around pivot
    int partition_index = left;
    for (int i = left + 1; i <= right; ++i) {
        if (input_array[i] < input_array[left]) {
            // This element should be moved to the left of partition_index
            ++partition_index;
            swap(input_array, i, partition_index);
        }
    }
    swap(input_array, left, partition_index);
    
    // Recurse on the left and right of pivot subarrays
    qsort_v1(input_array, left, pivot - 1);
    qsort_v1(input_array, pivot + 1, right);
}


bool is_not_descending(int input_arr[], int size) {
    for (int i = 1; i < size; ++i) {
        if (input_arr[i - 1] > input_arr[i]) {
            return false;
        }
    }
    return true;
}


void print_array(char prefix[], int input_array[], int size) {
    printf("%s array:[ ", prefix);
    for (int i = 0; i < size; ++i) {
        printf("%d ", input_array[i]);
    }
    printf("]\n");
}

int main() {
    printf("Running tests for simple_quick_sort\n");

    int input_array[MAX_ARR_SZ] = {0};
    bool debug = true;

    unsigned int num_failed = 0;
    for (int size = 2; size < (MAX_ARR_SZ + 1); ++size) {
        for (int iteration = 0; iteration < NUM_ITERATIONS; ++iteration) {
            fill_array(input_array, size, iteration);
            if (debug) {
                printf("\nRunning size = %d and iteration = %d\n", size, iteration);
                print_array("Before", input_array, size);
            }
            qsort_v1(input_array, 0, size - 1);

            if (debug) {
                print_array("After", input_array, size);
            }

            if (!is_not_descending(input_array, size)) {
                print_array("Failed", input_array, size);
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
