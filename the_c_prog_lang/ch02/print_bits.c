#include <stdio.h>


const unsigned int size = sizeof(int) * 8;

void fill_bits(char bits[], int n) {
    int i = 0;
    for(i = 0; i < size; ++i) {
        bits[i] = 0;
    }
    bits[i] = '\0';

    for (i = 0; i < size; ++i) {
        const int bit = n & (1 << (size - i - 1));
        bits[i] = bit ? '1' : '0';
    }
}

int binary_to_dec(char bits[]) {
    int n = 0;
    int sign_value = 1;
    for (int i = 1; bits[i] != '\0'; ++i) {
        int value = (bits[i] == '1') ? 1 : 0;
        n = value + n * 2;
        sign_value <<= 1;
    }
    int sign_bit = (bits[0] == '1') ? 1 : 0;
    sign_value = -sign_bit * sign_value;
    return sign_value + n;

}

int main() {
    char bits[size + 1];
    const int num_bits_to_use = 15;
    
    printf("Running tests for print_bits\n");
    
    int debug = 0;
    unsigned int num_failed = 0;
    for (int n = -(1 << num_bits_to_use); n < (1 << num_bits_to_use); ++n) {
        fill_bits(bits, n);
        int res = binary_to_dec(bits);
        if (debug != 0) {
            printf("n = %5d, bits = %s, converted value = %5d\n", n, bits, res);
        }
        if (res != n) {
            printf("FAILED for n = %5d, bits = %s and result = %5d\n", n, bits, res);
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
