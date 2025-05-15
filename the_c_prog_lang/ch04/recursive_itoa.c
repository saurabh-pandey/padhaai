#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define MAX_ARR_SZ 1000

const int NUM_ITERATIONS = 10;
const int MIN_ARR_VAL = -5 * MAX_ARR_SZ;
const int MAX_ARR_VAL = 5 * MAX_ARR_SZ;


int recursive_itoa_impl(int num, char result[], int depth) {
    const int new_num = num / 10;
    if (new_num > 0) {
        depth = recursive_itoa_impl(new_num, result, depth);
    }
    result[depth] = '0' + num % 10;
    return depth + 1;
}


void recursive_itoa(int num, char result[]) {
    int depth = 0;
    if (num < 0) {
        result[0] = '-';
        depth = 1;
        num = -num;
    }
    const int len = recursive_itoa_impl(num, result, depth);
    result[len] = '\0';
    printf("=> %d len = %d\n", num, len);
}


typedef struct test_data {
    int input;
    char expected[12];
} test_data;


bool compare_strings(char s1[], char s2[]) {
    int i = 0;
    while (true) {
        if (s1[i] != s2[i]) {
            return false;
        }
        if (s1[i] == '\0') {
            break;
        }
        ++i;
    }
    return true;
}


int main() {
    bool debug = true;
    printf("Running tests for recursive_itoa\n");

    test_data arr [] = {
        {123, "123"},
        {1, "1"},
        {42, "42"},
        {3, "3"},
        {105, "105"},
        {-1, "-1"},
        {-10, "-10"},
        {-42, "-42"},
        {-123, "-123"},
        {0, "0"},
    };

    unsigned int num_failed = 0;
    for (int i = 0; i < sizeof(arr)/sizeof(test_data); ++i) {
        char result[12] = {'\0'};
        recursive_itoa(arr[i].input, result);
        if (debug) {
            printf("Input = %d, expected = %s and result = %s\n",
                   arr[i].input,
                   arr[i].expected,
                   result);
        }
        if (!compare_strings(result, arr[i].expected)) {
            printf("FAILED for input = %d, expected = %s and result = %s\n",
                   arr[i].input,
                   arr[i].expected,
                   result);
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
