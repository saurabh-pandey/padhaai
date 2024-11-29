#include <stdio.h>
#include <stdbool.h>


// 2 comparison binary search
int binary_search_v1(int x, int nums[], int size) {
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


// Single comparison binary search
int binary_search_v2(int x, int nums[], int size) {
    if (size == 0) {
        return -1;
    }
    
    int begin = 0;
    int end = size - 1;
    while(begin < end - 1) {
        int mid = (begin + end) / 2;
        if (x < nums[mid]) {
            end = mid - 1;
        } else {
            begin = mid;
        }
    }
    if (nums[begin] == x) {
        return begin;
    } else if (nums[end] == x) {
        return end;
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
        {0, {}, 0, -1},
        {1, {0, 2, 4, 6}, 4, -1},
        {3, {0, 2, 4, 6}, 4, -1},
        {5, {0, 2, 4, 6}, 4, -1},
        {1, {0, 2, 4}, 3, -1},
        {3, {0, 2, 4}, 3, -1}
    };

    unsigned int num_failed = 0;
    for (int i = 0; i < sizeof(arr)/sizeof(test_data); ++i) {
        const unsigned index1 = binary_search_v1(arr[i].x, arr[i].nums, arr[i].size);
        const unsigned index2 = binary_search_v2(arr[i].x, arr[i].nums, arr[i].size);

        if (debug) {
            printf("x = %d, expected = %d, result1 = %d, , result2 = %d\n",
                   arr[i].x,
                   arr[i].expected,
                   index1,
                   index2);
        }
        if ((index1 != arr[i].expected) || (index2 != arr[i].expected)) {
            printf("x = %d, expected = %d, result1 = %d, , result2 = %d\n",
                   arr[i].x,
                   arr[i].expected,
                   index1,
                   index2);
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
