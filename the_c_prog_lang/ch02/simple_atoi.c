#include <math.h>
#include <stdio.h>

// int simple_atoi(const char inp[]) {
//     int i = 0;
//     for (i = 0; inp[i] != '\0'; ++i) {
//         printf("%c, %d\n", inp[i], inp[i]);
//     }
//     printf("Size = %d\n", i);
//     unsigned int size = i;
//     int n = 0;
//     // unsigned pow = 1;
//     for (i = 0; inp[i] != '\0'; ++i) {
//         n += pow(10, (size - i - 1)) * (inp[i] - 48);
//     }
//     return n;
// }

int simple_atoi(const char inp[]) {
    int i = 0;
    int n = 0;
    for (i = 0; inp[i] != '\0'; ++i) {
        // printf("%c, %d\n", inp[i], inp[i]);
        if (inp[i] >= '0' && inp[i] <= '9') {
            n = 10 * n + (inp[i] - '0');
        } else {
            return -1;
        }
    }
    printf("n = %d\n", n);
    return n;
}

typedef struct test_data {
    char input[12];
    int value;
} test_data;

int main() {
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
        const int result = simple_atoi(arr[i].input);
        printf("Input = %s, expected = %d and result = %d\n", arr[i].input, arr[i].value, result);
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
