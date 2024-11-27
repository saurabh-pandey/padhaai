#include <stdio.h>
#include <stdbool.h>

#include "bits_helper.h"


#define UNSIGNED_SIZE (sizeof(unsigned) * 8)


unsigned right_rotate(unsigned x, int n) {
    // Store first n bits which will be right shifted
    const unsigned first_n_bits = x & ~(~0 << n);
    // Right shift and to rotate copy the first n bits to the end
    return (x >> n) | (first_n_bits << (UNSIGNED_SIZE - n));
}


void fill_unsigned_to_bits(unsigned num, char bits[]) {
    int i = 0;
    for (i = 0; i < UNSIGNED_SIZE; ++i) {
        bits[i] = num & (1 << (UNSIGNED_SIZE - i - 1)) ? '1' : '0';
    }
    bits[i] = '\0';
}


void right_rotate_bits_array(char bits[], int n) {
    for (int i = 0; i < n; ++i) {
        char temp = bits[UNSIGNED_SIZE - 1];
        for (int j = UNSIGNED_SIZE - 1; j > 0; --j) {
            bits[j] = bits[j - 1];
        }
        bits[0] = temp;
    }
}


typedef struct test_data {
    unsigned x;
    int n;
} test_data;


int main() {
    bool debug = false;
    
    printf("Running tests for right_rotate_bits\n");

    test_data arr [] = {
        {0, 3},
        {0, 0},
        {0, 10},
        {1, 1},
        {2, 1},
        {3, 1},
        {4, 1},
        {4, 2},
        {8, 1},
        {8, 2},
        {8, 3},
        {23, 1},
        {1001, 5},
        {4999, 3}
    };

    unsigned int num_failed = 0;
    for (int i = 0; i < sizeof(arr)/sizeof(test_data); ++i) {
        unsigned rotated = right_rotate(arr[i].x, arr[i].n);
        
        char original_bits[UNSIGNED_SIZE + 1] = {'0'};
        fill_unsigned_to_bits(arr[i].x, original_bits);
        
        right_rotate_bits_array(original_bits, arr[i].n);
        
        unsigned rotated_bits_result = convert_bits_to_unsigned(original_bits);
        
        if (debug) {
            printf("Input = %u, n = %d, expected = %u and result = %u\n",
                   arr[i].x,
                   arr[i].n,
                   rotated_bits_result,
                   rotated);
        }
        if (rotated_bits_result != rotated) {
            printf("Input = %u, n = %d, expected = %u and result = %u\n",
                   arr[i].x,
                   arr[i].n,
                   rotated_bits_result,
                   rotated);
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
