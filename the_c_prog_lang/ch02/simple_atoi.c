#include <math.h>
#include <stdbool.h>
#include <stdio.h>


// My original attempt
int simple_atoi_v1(const char inp[]) {
    int i = 0;
    for (i = 0; inp[i] != '\0'; ++i) {
        if (inp[i] < '0' || inp[i] > '9') {
            return -1;
        } 
    }
    unsigned int size = i;
    int n = 0;
    // unsigned pow = 1;
    for (i = 0; inp[i] != '\0'; ++i) {
        n += pow(10, (size - i - 1)) * (inp[i] - 48);
    }
    return n;
}

// Better book version
int simple_atoi_v2(const char inp[]) {
    int i = 0;
    int n = 0;
    for (i = 0; inp[i] != '\0'; ++i) {
        if (inp[i] >= '0' && inp[i] <= '9') {
            n = 10 * n + (inp[i] - '0');
        } else {
            return -1;
        }
    }
    return n;
}

typedef struct test_data {
    char input[12];
    int value;
} test_data;

int main() {
    bool debug = false;
    
    printf("Running tests for simple_atoi\n");

    test_data arr [] = {
        {"1", 1},
        {"42", 42},
        {"03", 3},
        {"005", 5},
        {"1002", 1002},
        {"320", 320},
        {"0300", 300},
        {"a", -1},
        {"123a", -1},
        {"-1", -1},
        {"-2", -1},
        {"-32", -1},
        {"$#@", -1}
    };

    unsigned int num_failed = 0;
    for (int i = 0; i < sizeof(arr)/sizeof(test_data); ++i) {
        const int result1 = simple_atoi_v1(arr[i].input);
        const int result2 = simple_atoi_v2(arr[i].input);
        if (debug) {
            printf("Input = %s, expected = %d and result = %d\n",
                   arr[i].input,
                   arr[i].value,
                   result1);
            printf("Input = %s, expected = %d and result = %d\n",
                   arr[i].input,
                   arr[i].value,
                   result2);
        }
        if (result1 != arr[i].value) {
            printf("FAILED v1 input = %s, expected = %d and result1 = %d\n",
                   arr[i].input,
                   arr[i].value,
                   result1);
            ++num_failed;
        }
        if (result2 != arr[i].value) {
            printf("FAILED v2 input = %s, expected = %d and result2 = %d\n",
                   arr[i].input,
                   arr[i].value,
                   result2);
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
