#include <stdio.h>
#include <stdbool.h>

#define MAX_STR_LEN 20
#define SMALL_STR_LEN 10


bool my_strend(char *s, char *t) {
    size_t s_sz = 0;
    while (*s != '\0') {
        ++s;
        ++s_sz;
    }

    size_t t_sz = 0;
    while (*t != '\0') {
        ++t;
        ++t_sz;
    }

    if (t_sz > s_sz) {
        return false;
    }

    for (int i = 0; i < t_sz; ++i) {
        if (*(s - i - 1) != *(t - i - 1)) {
            return false;
        }
    }

    return true;
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
    bool result;
} test_data;


int main() {
    bool debug = false;
    
    printf("Running tests for simple_strend\n");

    test_data tests[] = {
        {"abc", "bc", true},
        {"a", "a", true},
        {"b", "", true},
        {"", "c", false},
        {"123", "456", false},
        {"123", "123", true},
        {"123", "12", false},
        {"123", "1234", false},
        {"123", "23", true},
        {"12345", "34", false}
    };

    unsigned int num_failed = 0;
    for (int i = 0; i < sizeof(tests)/sizeof(test_data); ++i) {
        const bool result = my_strend(tests[i].s, tests[i].t);

        if (debug) {
            printf("s = %s, t = %s, expected = %d, result = %d\n",
                   tests[i].s,
                   tests[i].t,
                   tests[i].result,
                   result);
        }
        if (result != tests[i].result) {
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
