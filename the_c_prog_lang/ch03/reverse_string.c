#include <stdbool.h>
#include <stdio.h>
#include <string.h>


void reverse_string(char s[]) {
    for (int i = 0, j = strlen(s) - 1; i < j; ++i, --j) {
        char temp = s[i];
        s[i] = s[j];
        s[j] = temp;
    }
}


typedef struct test_data {
    char input[20];
    char output[20];
} test_data;


bool compare_string(char s1[], char s2[]) {
    int i = 0;
    while(true) {
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
    
    printf("Running tests for reverse_string\n");

    test_data arr [] = {
        {"abc", "cba"},
        {"ab", "ba"},
        {"a", "a"},
        {"", ""},
        {"aba", "aba"},
        {"aa", "aa"},
        {"abcdef", "fedcba"},
        {"abab", "baba"}
    };

    unsigned int num_failed = 0;
    for (int i = 0; i < sizeof(arr)/sizeof(test_data); ++i) {
        if (debug) {
            printf("input = %s\n", arr[i].input);
        }
        
        reverse_string(arr[i].input);
        
        if (debug) {
            printf("output = %s, expected = %s\n", arr[i].input, arr[i].output);
        }
        if (!compare_string(arr[i].input, arr[i].output)) {
            printf("expected = %s, result = %s\n", arr[i].output, arr[i].input);
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
