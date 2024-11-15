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

int main() {
    char bits[size + 1];
    const int num_bits_to_use = 4;
    for (int n = -(1 << num_bits_to_use); n < (1 << num_bits_to_use); ++n) {
        fill_bits(bits, n);
        printf("%d: %s\n", n, bits);
    }
    return 0;
}
