#include <stdio.h>
#include <stdbool.h>

#define MAX_STR_LEN 20
#define SMALL_STR_LEN 10


void my_strcat(char *s, char *t) {
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

int my_strcmp(char *s, char *t) {
    while (*s == *t) {
        if (*s == '\0') {
            return 0;
        }
        ++s;
        ++t;
    }

    return (*s - *t);
}

typedef struct test_data {
    char s[MAX_STR_LEN];
    char t[SMALL_STR_LEN];
    char *result;
} test_data;


int main() {
    bool debug = false;
    
    printf("Running tests for simple_strcat\n");

    test_data tests[] = {
        {"abc", "ba", "abcba"},
        {"a", "a", "aa"},
        {"b", "", "b"},
        {"", "c", "c"},
        {"123", "456", "123456"}
    };

    unsigned int num_failed = 0;
    for (int i = 0; i < sizeof(tests)/sizeof(test_data); ++i) {
        my_strcat(tests[i].s, tests[i].t);

        if (debug) {
            printf("s = %s, t = %s, expected = %s\n", tests[i].s, tests[i].t, tests[i].result);
        }
        if (my_strcmp(tests[i].s, tests[i].result) != 0) {
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
