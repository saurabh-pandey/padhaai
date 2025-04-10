#include <stdio.h>
#include <stdbool.h>

#include "bits_helper.h"


#define SIZE 11

int bitcount_v1(unsigned x) {
    int count = 0;
    while (x > 0) {
        if (x & 1) {
            ++count;
        }
        x >>= 1;
    }
    return count;
}


int bitcount_v2(unsigned x) {
    int count = 0;
    while (x > 0) {
        ++count;
        x &= (x - 1);
    }
    return count;
}


int count_on_bits(char bits[]) {
    int count = 0;
    for (int i = 0; bits[i] != '\0'; ++i) {
        if (bits[i] == '1') {
            ++count;
        }
    }
    return count;
}


typedef struct test_data {
    char bits[SIZE];
} test_data;


int main() {
    bool debug = false;
    
    printf("Running tests for bitcount\n");

    test_data arr [] = {
        {"0000000000"},
        {"0000000001"},
        {"0000000010"},
        {"0000000011"},
        {"1111111111"},
        {"1010101010"},
        {"0101010101"},
        {"0000011111"},
        {"1111100000"}
    };

    unsigned int num_failed = 0;
    for (int i = 0; i < sizeof(arr)/sizeof(test_data); ++i) {
        unsigned x = convert_bits_to_unsigned(arr[i].bits);
        
        int result1 = bitcount_v1(x);
        int result2 = bitcount_v2(x);
        
        int expected = count_on_bits(arr[i].bits);

        if (debug) {
            printf("Input = %s, x = %u, expected = %d, result1 = %d and result2 = %d\n",
                   arr[i].bits,
                   x,
                   expected,
                   result1,
                   result2);
        }
        if ((result1 != expected) || (result2 != expected)) {
            printf("Input = %s, x = %u, expected = %d, result1 = %d and result2 = %d\n",
                   arr[i].bits,
                   x,
                   expected,
                   result1,
                   result2);
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
