#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define MAX_CHAR_SIZE 11


int recursive_reverse(char input[]) {
    return -1;
}


typedef struct test_data {
    char input[MAX_CHAR_SIZE];
    char expected[MAX_CHAR_SIZE];
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
    bool debug = false;
    printf("Running tests for recursive_reverse\n");

    test_data arr [] = {
        {"ab", "ba"},
        {"a", "a"},
        {"abc", "cba"},
        {"", ""},
        {"1234", "4321"},
        {"~!@#", "#@!~"},
        {"aa", "aa"},
        {"ccc", "ccc"},
    };

    unsigned int num_failed = 0;
    for (int i = 0; i < sizeof(arr)/sizeof(test_data); ++i) {
        recursive_reverse(arr[i].input);
        if (debug) {
            printf("Result = %s, expected = %s\n",
                   arr[i].input,
                   arr[i].expected);
        }
        if (!compare_strings(arr[i].input, arr[i].expected)) {
            printf("FAILED for input = %s, expected = %s\n",
                   arr[i].input,
                   arr[i].expected);
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
