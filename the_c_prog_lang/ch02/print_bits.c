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
    int sign_bit = (bits[0] == '1') ? 1 : 0;
    int sign_value = -1 * sign_bit;
    // printf("  %d, %d\n", sign_bit, sign_value);
    for (int i = 1; bits[i] != '\0'; ++i) {
        int value = (bits[i] == '1') ? 1 : 0;
        n = value + n * 2;
        sign_value *= 2;
        // printf("  %d, %d\n", sign_bit, sign_value);
    }
    // printf("  %d, %d\n", sign_value, n);
    return sign_value + n;

}

int main() {
    char bits[size + 1];
    const int num_bits_to_use = 4;
    for (int n = -(1 << num_bits_to_use); n < (1 << num_bits_to_use); ++n) {
        fill_bits(bits, n);
        printf("%d: %s\n", n, bits);
        int res = binary_to_dec(bits);
        printf("%s: %d\n\n", bits, res);
    }
    return 0;
}
