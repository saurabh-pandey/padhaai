#include <stdio.h>
#include <stdbool.h>

#define MAX_CHAR_DIGITS 12

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

    unsigned int num_failed = 0;
    for (int i = -1000; i <= 1000; ++i) {
        // TEST OCTAL
        char result[MAX_CHAR_DIGITS] = {'\0'};
        simple_itob(i, 8, result);
        char expected[MAX_CHAR_DIGITS] = {'\0'};
        if (i < 0) {
            snprintf(expected, MAX_CHAR_DIGITS, "-%o", -i);
        } else {
            snprintf(expected, MAX_CHAR_DIGITS, "%o", i);
        }
        
        if (debug) {
            printf("Input = %d, base = 8, expected = %s and result = %s\n", i, expected, result);
        }

        if (!compare_strings(result, expected)) {
            printf("FAILED for input = %d, base = 8, expected = %s and result = %s\n",
                   i,
                   expected,
                   result);
            ++num_failed;
        }

        // TEST HEX
        simple_itob(i, 16, result);
        if (i < 0) {
            snprintf(expected, MAX_CHAR_DIGITS, "-%X", -i);
        } else {
            snprintf(expected, MAX_CHAR_DIGITS, "%X", i);
        }
        if (debug) {
            printf("Input = %d, base = 16, expected = %s and result = %s\n", i, expected, result);
        }
        if (!compare_strings(result, expected)) {
            printf("FAILED for input = %d, base = 16, expected = %s and result = %s\n",
                   i,
                   expected,
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
