#include <stdio.h>
#include <stdbool.h>


void simple_itoa(int num, char output[]) {
    const int sign = num < 0 ? -1 : 1;
    int i = 0;
    do {
        const int digit = sign * (num % 10);
        output[i] = '0' + digit;
        ++i;
        num /= 10;
    } while (num != 0);
    
    // Add sign char
    if (sign == -1) {
        output[i] = '-';
        ++i;
    }
    
    // reverse here noting that i now points next to the last char
    for (int start = 0, end = i - 1; start < end; ++start, --end) {
        char temp = output[start];
        output[start] = output[end];
        output[end] = temp;
    }
    
    output[i] = '\0';
}

typedef struct test_data {
    int input;
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
    
    printf("Running tests for simple_itoa\n");

    test_data arr [] = {
        {1, "1"},
        {42, "42"},
        {3, "3"},
        {105, "105"},
        {-1, "-1"},
        {-10, "-10"},
        {-42, "-42"},
        {-123, "-123"},
        {0, "0"},
    };

    unsigned int num_failed = 0;
    for (int i = 0; i < sizeof(arr)/sizeof(test_data); ++i) {
        char result[12] = {'\0'};
        simple_itoa(arr[i].input, result);
        if (debug) {
            printf("Input = %d, expected = %s and result = %s\n",
                   arr[i].input,
                   arr[i].expected,
                   result);
        }
        if (!compare_strings(result, arr[i].expected)) {
            printf("FAILED for input = %d, expected = %s and result1 = %s\n",
                   arr[i].input,
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
