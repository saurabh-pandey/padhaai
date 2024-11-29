#include <stdio.h>
#include <stdbool.h>


int binary_search(int x, int nums[], int size) {
    int begin = 0;
    int end = size - 1;
    while(begin <= end) {
        int mid = (begin + end) / 2;
        if (x < nums[mid]) {
            end = mid - 1;
        } else if (x > nums[mid]) {
            begin = mid + 1;
        } else {
            return mid;
        }
    }
    return -1;
}


typedef struct test_data {
    int x;
    int nums[20];
    int size;
    int expected;
} test_data;


int main() {
    bool debug = false;
    
    printf("Running tests for binary_search\n");

    test_data arr [] = {
        {1, {0, 1, 2}, 3, 1},
        {2, {0, 1, 2}, 3, 2},
        {0, {0, 1, 2}, 3, 0},
        {-1, {0, 1, 2}, 3, -1},
        {3, {0, 1, 2}, 3, -1},
        {1, {0, 1}, 2, 1},
        {0, {0, 1}, 2, 0},
        {-1, {0, 1}, 2, -1},
        {2, {0, 1}, 2, -1},
        {0, {0}, 1, 0},
        {-1, {0}, 1, -1},
        {1, {0}, 1, -1},
        {1, {}, 0, -1},
        {0, {}, 0, -1}
    };

    unsigned int num_failed = 0;
    for (int i = 0; i < sizeof(arr)/sizeof(test_data); ++i) {
        const unsigned index = binary_search(arr[i].x, arr[i].nums, arr[i].size);

        if (debug) {
            printf("x = %d, expected = %d, result = %d\n",
                   arr[i].x,
                   arr[i].expected,
                   index);
        }
        if (index != arr[i].expected) {
            printf("x = %d, expected = %d, result = %d\n",
                   arr[i].x,
                   arr[i].expected,
                   index);
            ++num_failed;
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
