#include <stdio.h>
#include <stdbool.h>


int to_lower(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + 'a' - 'A';
    } else {
        return c;
    }
}


typedef struct test_data
{
    char input;
    char output;
} test_data;


int main() {
    bool debug = false;
    
    printf("Running tests for simple_tolower\n");

    test_data arr [] = {
        {'A', 'a'},
        {'D', 'd'},
        {'H', 'h'},
        {'K', 'k'},
        {'Z', 'z'},
        {'1', '1'},
        {'f', 'f'},
        {'#', '#'}
    };

    unsigned int num_failed = 0;
    for (int i = 0; i < sizeof(arr)/sizeof(test_data); ++i) {
        int result = to_lower(arr[i].input);
        if (debug) {
            printf("Input = %c, expected = %c and result = %c\n",
                   arr[i].input,
                   arr[i].output,
                   result);
        }
        if (arr[i].output != result) {
            printf("FAILED input = %c, expected = %c and result1 = %c\n",
                   arr[i].input,
                   arr[i].output,
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