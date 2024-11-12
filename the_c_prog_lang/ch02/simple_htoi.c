#include <stdio.h>
#include <stdbool.h>

int simple_htoi(char input[]) {
    // First 2 char of hex should be 0x or 0X
    if (input[0] != '0') {
        return -1;
    }
    if (input[1] != 'x' && input[1] != 'X') {
        return -1;
    }
    // Check we have reached the end here so the input is just "0x" or "0X"
    if (input[2] == '\0') {
        return -1;
    }

    int n = 0;
    for (int i = 2; input[i] != '\0'; ++i) {
        int digit_value = -1;
        if (input[i] >= '0' && input[i] <= '9') {
            digit_value = input[i] - '0';
        } else if (input[i] >= 'A' && input[i] <= 'F') {
            digit_value = 10 + input[i] - 'A';
        } else if (input[i] >= 'a' && input[i] <= 'f') {
            digit_value = 10 + input[i] - 'a';
        } else {
            return -1;
        }
        n = n * 16 + digit_value;
    }
    return n;
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
        {"0x", -1},
        {"0X", -1},
        {"0xg", -1},
        {"0Xh", -1},
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
            printf("FAILED input = %s, expected = %d and result = %d\n",
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
