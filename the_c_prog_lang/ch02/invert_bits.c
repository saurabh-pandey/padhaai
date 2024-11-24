#include <stdio.h>
#include <stdbool.h>

#define SIZE 12


unsigned invert_bits(unsigned x, int p, int n) {
    unsigned n_on_bits = ~(~0 << n);
    // NOTE: XOR with 1 flips the bits and with 0 doesn't
    return x ^ (n_on_bits << (p - n + 1));
}

unsigned convert_bits_to_unsigned(char bits[]) {
    unsigned n = 0;
    for (int i = 0; bits[i] != '\0'; ++i) {
        unsigned value = bits[i] == '1' ? 1 : 0;
        n = value + n * 2;
    }
    return n;
}

void fill_unsigned_to_bits(unsigned result, char result_bits[]) {
    int i = SIZE - 2;
    while ((result != 0) && (i >= 0)) {
        result_bits[i] = (result & 1) ? '1' : '0';
        result >>= 1;
        --i;
    }
}


typedef struct test_data {
    char input[12];
    int p;
    int n;
    char result[12];
} test_data;

int main() {
    bool debug = true;
    
    printf("Running tests for getbits\n");

    // NOTE: All string are of size SIZE
    test_data arr [] = {
        {"00000000000", 3, 2, "00000001100"},
        {"00000001100", 3, 2, "00000000000"},
        {"11111111111", 3, 2, "11111110011"},
        {"11111111111", 10, 11, "00000000000"},
        {"00000000000", 10, 11, "11111111111"},
        {"11011010011", 7, 3, "11000110011"},
        {"11011010011", 2, 3, "11011010100"}
    };

    unsigned int num_failed = 0;
    for (int i = 0; i < sizeof(arr)/sizeof(test_data); ++i) {
        unsigned x = convert_bits_to_unsigned(arr[i].input);
        const unsigned result = invert_bits(x, arr[i].p, arr[i].n);
        char result_bits[12] = "00000000000";
        fill_unsigned_to_bits(result, result_bits);
        if (debug) {
            printf("Input = %s, p = %d, n = %d, expected = %s and result = %s\n",
                   arr[i].input,
                   arr[i].p,
                   arr[i].n,
                   arr[i].result,
                   result_bits);
        }
        for (int j = SIZE - 1; j >= 0; --j) {
            if (arr[i].result[j] != result_bits[j]) {
                printf("Failed for Input = %s, p = %d, n = %d, expected = %s and result = %s\n",
                       arr[i].input,
                       arr[i].p,
                       arr[i].n,
                       arr[i].result,
                       result_bits);
                ++num_failed;
            }
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
