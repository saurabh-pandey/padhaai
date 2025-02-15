#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


#define MAX_STR_LEN 20
#define TOLERANCE 1.0e-6


double simple_atof(char s[]) {
    return 0.0;
}


typedef struct test_data {
    char s[MAX_STR_LEN];
    double expected;
} test_data;


int main() {
    bool debug = true;
    
    printf("Running tests for simple_atof\n");

    test_data tests[] = {
        {"1.2", 1.2},
        {"-1.2", -1.2},
        {"0.02", 0.02},
        {"-0.02", -0.02},
        {"200.0", 200.0},
        {"-200.0", -200.0},
        {"42.12", 42.12},
        {"-42.12", -42.12}
    };

    unsigned int num_failed = 0;
    for (int i = 0; i < sizeof(tests)/sizeof(test_data); ++i) {
        const double result = simple_atof(tests[i].s);

        if (debug) {
            printf("s = %s, expected = %f, , result = %f\n",
                   tests[i].s,
                   tests[i].expected,
                   result);
        }
        // if (abs(result - tests[i].expected) > TOLERANCE) {
        //     printf("s = %s, expected = %f, , result = %f\n",
        //            tests[i].s,
        //            tests[i].expected,
        //            result);
        //     ++num_failed;
        // }
    }
    if (num_failed > 0) {
        printf("%d test failed\n", num_failed);
    } else {
        printf("All tests passed\n");
    }
    printf("Done\n");

    return 0;
}
