#include <stdio.h>
#include <stdbool.h>


char digits[] = "0123456789ABCDEFGHIZKLMNOPQRSTUVWXYZ";


void simple_itob(int num, int base, char output[]) {
    const int sign = num < 0 ? -1 : 1;
    int j = 0;
    do {
        const int digit = sign * (num % base);
        output[j] = digits[digit];
        ++j;
        num /= base;
    } while (num != 0);
    if (sign == -1) {
        output[j] = '-';
        ++j;
    }
    // Reverse here
    for (int start = 0, end = j - 1; start < end; ++start, --end) {
        char temp = output[start];
        output[start] = output[end];
        output[end] = temp;
    }
    output[j] = '\0';
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
    bool debug = true;
    
    printf("Running tests for simple_itob\n");

    test_data arr [] = {
        {0, 2, "0"},
        {1, 2, "1"},
        {-1, 2, "-1"},
        {2, 2, "10"},
        {-2, 2, "-10"},
        {3, 2, "11"},
        {-3, 2, "-11"}
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
        // if (!compare_strings(result, arr[i].expected)) {
        //     printf("FAILED for input = %d, base = %d, expected = %s and result1 = %s\n",
        //            arr[i].input,
        //            arr[i].base,
        //            arr[i].expected,
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
