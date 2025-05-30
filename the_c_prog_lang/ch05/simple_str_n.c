#include <stdio.h>
#include <stdbool.h>

#define MAX_STR_LEN 20
#define SMALL_STR_LEN 10


void my_strncpy(char *s, char *t, int n) {
    while ((*s = *t) != '\0') {
        ++s;
        ++t;
    }
}

void my_strncat(char *s, char *t) {
    while (*s != '\0') {
        ++s;
    }

    while (*t != '\0') {
        *s = *t;
        ++s;
        ++t;
    }
    *s = '\0';
}

int my_strncmp(char *s, char *t) {
    while (*s == *t) {
        if (*s == '\0') {
            return 0;
        }
        ++s;
        ++t;
    }

    return (*s - *t);
}

typedef struct strncpy_test_data {
    char s[MAX_STR_LEN];
    int n;
    char *expected;
} strncpy_test_data;


int main() {
    bool debug = false;
    
    printf("Running tests for simple_str_n\n");

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
        my_strcpy(t, strncpy_tests[i].s, strncpy_tests[i].n);

        if (debug) {
            printf("s = %s, n = %d, t = %s, expected\n",
                   strncpy_tests[i].s,
                   strncpy_tests[i].n,
                   t,
                   strncpy_tests[i].expected);
        }
        const int cmp_res = my_strncmp(t, strncpy_tests[i].expected);
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

    return 0;
}
