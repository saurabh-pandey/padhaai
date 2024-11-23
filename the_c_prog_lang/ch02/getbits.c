#include <stdio.h>
#include <stdbool.h>

#define SIZE 12


unsigned get_bits(unsigned x, int p, int n) {
    return (x >> (p - n + 1)) & ~(~0 << n);
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
    bool debug = false;
    
    printf("Running tests for getbits\n");

    // NOTE: All string are of size SIZE
    test_data arr [] = {
        {"00000000000", 3, 2, "00000000000"},
        {"00000001100", 3, 2, "00000000011"},
        {"00000010100", 4, 3, "00000000101"},
        {"11111110100", 10, 7, "00001111111"},
        {"11111111111", 4, 2, "00000000011"},
        {"11111110100", 10, 11, "11111110100"},
    };

    unsigned int num_failed = 0;
    for (int i = 0; i < sizeof(arr)/sizeof(test_data); ++i) {
        unsigned x = convert_bits_to_unsigned(arr[i].input);
        const unsigned result = get_bits(x, arr[i].p, arr[i].n);
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
