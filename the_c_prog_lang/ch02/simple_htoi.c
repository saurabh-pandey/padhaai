#include <stdio.h>
#include <stdbool.h>

int simple_htoi(char input[]) {
    // for (int i = 0; input[i] != '\0'; ++i) {

    // }
    return -1;
}


typedef struct test_data {
    char input[12];
    int value;
} test_data;

int main() {
    bool debug = false;
    
    printf("Running tests for simple_htoi\n");

    test_data arr [] = {
        {"0x1", 1},
        {"0X1", 1},
        {"0x0", 0},
        {"0X0", 0},
        {"0x9", 9},
        {"0Xa", 10},
        {"0xb", 11},
        {"0Xc", 12},
        {"0xd", 13},
        {"0Xe", 14},
        {"0xf", 15},
        {"1", -1},
        {"1f", -1},
        {"", -1},
        {"a", -1},
        {"123a", -1},
        {"-1", -1},
        {"-2", -1},
        {"32", -1},
        {"$#@", -1}
    };

    unsigned int num_failed = 0;
    for (int i = 0; i < sizeof(arr)/sizeof(test_data); ++i) {
        const int result = simple_htoi(arr[i].input);
        if (debug) {
            printf("Input = %s, expected = %d and result = %d\n",
                   arr[i].input,
                   arr[i].value,
                   result);
        }
        if (result != arr[i].value) {
            printf("FAILED input = %s, expected = %d and result1 = %d\n",
                   arr[i].input,
                   arr[i].value,
                   result);
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
