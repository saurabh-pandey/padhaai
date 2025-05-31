#include <stdio.h>
#include <stdbool.h>

#define MAX_STR_LEN 20
#define SMALL_STR_LEN 10


int my_strncmp(char *s, char *t, int n) {
    while (n > 0 && (*s == *t)) {
        if (*s == '\0') {
            return 0;
        }
        ++s;
        ++t;
        --n;
    }

    return (*s - *t);
}


void my_strncpy(char *s, char *t, int n) {
    while (n > 0 && (*s = *t) != '\0') {
        ++s;
        ++t;
        --n;
    }
}

typedef struct strncpy_test_data {
    char s[MAX_STR_LEN];
    int n;
    char *expected;
} strncpy_test_data;

void run_strncpy_tests() {
    bool debug = false;
    
    printf("Running tests for simple_strncpy\n");

    strncpy_test_data strncpy_tests[] = {
        {"abc", 1, "a"},
        {"abc", 2, "ab"},
        {"abc", 3, "abc"},
        {"abc", 4, "abc"},
        {"abc", 5, "abc"},
        {"abc", 0, ""},
        {"abc", -1, ""},
        {"", 0, ""},
        {"", 1, ""},
        {"", -1, ""}
    };

    unsigned int num_failed = 0;
    for (int i = 0; i < sizeof(strncpy_tests)/sizeof(strncpy_test_data); ++i) {
        char t[MAX_STR_LEN] = "";
        my_strncpy(t, strncpy_tests[i].s, strncpy_tests[i].n);

        if (debug) {
            printf("s = %s, n = %d, t = %s, expected = %s\n",
                   strncpy_tests[i].s,
                   strncpy_tests[i].n,
                   t,
                   strncpy_tests[i].expected);
        }
        const int cmp_res = my_strncmp(t, strncpy_tests[i].expected, strncpy_tests[i].n);
        if (cmp_res != 0) {
            ++num_failed;
        }
    }
    if (num_failed > 0) {
        printf("%d test failed\n", num_failed);
    } else {
        printf("All tests passed\n");
    }
    printf("Done\n");
}


void my_strncat(char *s, char *t, int n) {
    while (*s != '\0') {
        ++s;
    }

    while (n > 0 && *t != '\0') {
        *s = *t;
        ++s;
        ++t;
        --n;
    }
    *s = '\0';
}


typedef struct strncat_test_data {
    char s[MAX_STR_LEN];
    char t[SMALL_STR_LEN];
    int n;
    char *expected;
} strncat_test_data;


void run_strncat_tests() {
    bool debug = false;
    
    printf("Running tests for simple_strncat\n");

    strncat_test_data strncat_tests[] = {
        {"abc", "ba", 2, "abcba"},
        {"abc", "ba", 1, "abcb"},
        {"abc", "ba", 0, "abc"},
        {"abc", "ba", -1, "abc"},
        {"abc", "ba", 3, "abcba"},
        {"abc", "ba", 4, "abcba"},
        {"", "1234", 0, ""},
        {"", "1234", 1, "1"},
        {"", "1234", 2, "12"},
        {"", "1234", 3, "123"},
        {"", "1234", 4, "1234"},
        {"", "1234", 5, "1234"},
        {"", "1234", 6, "1234"},
        {"", "1234", -1, ""},
        {"", "", 0, ""},
        {"", "", 1, ""},
        {"", "", -1, ""},
    };

    unsigned int num_failed = 0;
    for (int i = 0; i < sizeof(strncat_tests)/sizeof(strncat_test_data); ++i) {
        my_strncat(strncat_tests[i].s, strncat_tests[i].t, strncat_tests[i].n);

        if (debug) {
            printf("s = %s, n = %d, t = %s, expected = %s\n",
                   strncat_tests[i].s,
                   strncat_tests[i].n,
                   strncat_tests[i].t,
                   strncat_tests[i].expected);
        }
        const int cmp_res = my_strncmp(strncat_tests[i].s,
                                       strncat_tests[i].expected,
                                       strncat_tests[i].n);
        if (cmp_res != 0) {
            ++num_failed;
        }
    }
    if (num_failed > 0) {
        printf("%d test failed\n", num_failed);
    } else {
        printf("All tests passed\n");
    }
    printf("Done\n");
}


int main() {
    run_strncpy_tests();
    run_strncat_tests();
    return 0;
}
