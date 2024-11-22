#include <stdio.h>

unsigned getbits(unsigned x, int p, int n) {
    return 0;
}

unsigned convert_bits_to_unsigned(char bits[]) {
    return 0;
}

void fill_unsigned_to_bits(unsigned result, char result_bits[]) {
    return;
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

    test_data arr [] = {
        {"0000000", "0000000"},
    };

    unsigned int num_failed = 0;
    for (int i = 0; i < sizeof(arr)/sizeof(test_data); ++i) {
        unsigned x = convert_bits_to_unsigned(arr[i].input);
        const unsigned result = getbits(x, arr[i].p, arr[i].n);
        char result_bits[12];
        fill_unsigned_to_bits(result, result_bits);
        if (debug) {
            printf("Input = %s, p = %d, n = %d and result = %d\n",
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
