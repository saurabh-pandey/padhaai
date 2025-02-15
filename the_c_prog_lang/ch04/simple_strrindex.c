#include <stdio.h>
#include <stdbool.h>


#define MAX_STR_LEN 20


int str_len(char s[]) {
    int len = 0;
    while (s[len] != '\0') {
        ++len;
    }
    return len;
}


int simple_strrindex_buggy(char s[], char t[]) {
    const int len_s = str_len(s);
    if (len_s == 0) {
        return -1;
    }
    const int len_t = str_len(t);
    if (len_t == 0) {
        return -1;
    }
    int j = len_t - 1;
    for (int i = len_s - 1; i >=0; --i) {
        if (s[i] != t[j]) {
            // NOTE: It is this reset at the time of mismatch that is incorrect
            j = len_t - 1;
        } else {
            --j;
        }
        if (j < 0) {
            return i;
        }
    }
    return -1;
}


int simple_strrindex(char s[], char t[]) {
    const int len_s = str_len(s);
    if (len_s == 0) {
        return -1;
    }
    const int len_t = str_len(t);
    if (len_t == 0) {
        return -1;
    }
    
    for (int i = len_s - len_t; i >=0; --i) {
        bool is_found = true;
        for (int j = 0; j < len_t; ++j) {
            if (s[i + j] != t[j]) {
                is_found = false;
                break;
            }
        }
        if (is_found) {
            return i;
        }
    }
    return -1;
}


typedef struct test_data {
    char s[MAX_STR_LEN];
    char t[MAX_STR_LEN];
    int result;
} test_data;


int main() {
    bool debug = false;
    
    printf("Running tests for simple_strrindex\n");

    test_data tests[] = {
        {"abc", "a", 0},
        {"abc", "b", 1},
        {"abc", "c", 2},
        {"abc", "bc", 1},
        {"abcd", "cd", 2},
        {"abcd", "ab", 0},
        {"abab", "ab", 2},
        {"ababcdcd", "ab", 2},
        {"hhello", "hello", 1},
        {"aaab", "aab", 1},
        {"babababbaabaabbbbb", "baabb", 10}
    };

    unsigned int num_failed = 0;
    for (int i = 0; i < sizeof(tests)/sizeof(test_data); ++i) {
        const unsigned index = simple_strrindex(tests[i].s, tests[i].t);

        if (debug) {
            printf("s = %s, t = %s, expected = %d, , result = %d\n",
                   tests[i].s,
                   tests[i].t,
                   tests[i].result,
                   index);
        }
        if (index != tests[i].result) {
            printf("s = %s, t = %s, expected = %d, , result = %d\n",
                   tests[i].s,
                   tests[i].t,
                   tests[i].result,
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
