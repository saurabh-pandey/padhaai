#include <stdio.h>
#include <stdbool.h>

#define MAX_STR_LEN 20


void my_strcpy(char *s, char *t) {
    while ((*s = *t) != '\0') {
        ++s;
        ++t;
    }
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
    bool do_copy;
} test_data;


int main() {
    bool debug = true;
    
    printf("Running tests for string_op\n");

    test_data tests[] = {
        {"abc", true},
        {"babababbaabaabbbbb", true},
        {"cab", false}
    };

    unsigned int num_failed = 0;
    for (int i = 0; i < sizeof(tests)/sizeof(test_data); ++i) {
        char t[MAX_STR_LEN] = "";
        if (tests[i].do_copy) {
            my_strcpy(t, tests[i].s);
        }

        if (debug) {
            printf("s = %s, t = %s\n", tests[i].s, t);
        }
        const int cmp_res = my_strcmp(t, tests[i].s);
        if (tests[i].do_copy && cmp_res != 0) {
            ++num_failed;
        }
        if (!tests[i].do_copy && cmp_res == 0) {
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
