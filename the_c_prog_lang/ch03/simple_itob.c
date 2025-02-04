#include <stdio.h>
#include <stdbool.h>


void simple_itob(int num, int base, char output[]) {
    // TODO: Implement
}

typedef struct test_data {
    int input;
    int base;
    char expected[12];
} test_data;


bool compare_strings(char str1[], char str2[]) {
    int i = 0;
    while(true) {
        if (str1[i] != str2[i]) {
            return false;
        }
        if (str1[i] == '\0') {
            break;
        }
        ++i;
    }
    return true;
}


int main() {
    bool debug = false;
    
    printf("Running tests for simple_itob\n");

    test_data arr [] = {
        {0, 2, "0"},
        {1, 2, "1"},
        {2, 2, "10"},
        {3, 2, "11"}
    };

    unsigned int num_failed = 0;
    for (int i = 0; i < sizeof(arr)/sizeof(test_data); ++i) {
        char result[12] = {'\0'};
        simple_itob(arr[i].input, arr[i].base, result);
        if (debug) {
            printf("Input = %d, base = %d, expected = %s and result = %s\n",
                   arr[i].input,
                   arr[i].base,
                   arr[i].expected,
                   result);
        }
        if (!compare_strings(result, arr[i].expected)) {
            printf("FAILED for input = %d, base = %d, expected = %s and result1 = %s\n",
                   arr[i].input,
                   arr[i].base,
                   arr[i].expected,
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
