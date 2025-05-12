#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define MAX_ARR_SZ 100
#define MIN_ARR_VAL -500
#define MAX_ARR_VAL 500

void fill_array(int input_arr[], int size) {
    srand(time(NULL));

    for (int i = 0; i < size; ++i) {
        int val = MIN_ARR_VAL + (rand() % (MAX_ARR_VAL - MIN_ARR_VAL + 1));
        // printf("i = %d, Val = %d\n", i, val);
        input_arr[i] = val;
    }
}

// NOTE: left and right args are assumed to be inclusive
void qsort_v1(int input_array[], int left, int right) {
    // Input array of size 1 or less is already sorted
    if ((right - left + 1) < 2) {
        return;
    }

    // Input array is of size > 1
    const int pivot = (left + right) / 2;

    // Partition around pivot
    for (int i = left; i <= right; ++i) {
        if (input_array[i] < input_array[pivot]) {
            // This element should be moved to the left of pivot
        } else {
            // This element should be moved to the right of pivot
        }
    }
    // Here pivot should be at its rightful sorted position
    
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


int main() {
    printf("Running tests for simple_quick_sort\n");

    int input_array[MAX_ARR_SZ] = {0};

    unsigned int num_failed = 0;
    for (int size = 1; size < (MAX_ARR_SZ + 1); ++size) {
        for (int iteration = 0; iteration < 10; ++iteration) {
            fill_array(input_array, size);
            qsort_v1(input_array, 0, size - 1);

            if (!is_not_descending(input_array, size)) {
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