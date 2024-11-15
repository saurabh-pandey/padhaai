#include <stdio.h>

void fill_bits(char bits[], int n) {
    unsigned int size = sizeof(int);
    int i = 0;
    for(i = 0; i < size * 8; ++i) {
        bits[i] = 0;
    }
    bits[i] = '\0';

    for (i = 0; i < size * 8; ++i) {
        const int bit = n & (1 << ((size * 8) - i - 1));
        bits[i] = bit ? '1' : '0';
    }
}

int main() {
    char bits[sizeof(int) * 16];
    for (int n = -(1 << 4); n < (1 << 4); ++n) {
        fill_bits(bits, n);
        printf("%d: %s\n", n, bits);
    }
    return 0;
}
