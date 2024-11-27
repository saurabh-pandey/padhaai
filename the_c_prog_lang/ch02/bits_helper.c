#include "bits_helper.h"


unsigned convert_bits_to_unsigned(char bits[]) {
    unsigned n = 0;
    for (int i = 0; bits[i] != '\0'; ++i) {
        unsigned value = (bits[i] == '1') ? 1 : 0;
        n = value + (n << 1);
    }
    return n;
}
