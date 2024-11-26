#include <stdio.h>
#include <stdbool.h>


#define UNSIGNED_SIZE (sizeof(unsigned) * 8)


unsigned right_rotate(unsigned x, int n) {
    const unsigned first_n_bits = x & ~(~0 << n);
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


unsigned convert_bits_to_unsigned(char bits[]) {
    unsigned n = 0;
    for (int i = 0; bits[i] != '\0'; ++i) {
        unsigned value = (bits[i] == '1') ? 1 : 0;
        n = value + (n << 1);
    }
    return n;
}


typedef struct test_data {
    unsigned x;
    int n;
} test_data;


int main() {
    bool debug = false;
    
    printf("Running tests for right_rotate_bits\n");

    // NOTE: All string are of size SIZE
    test_data arr [] = {
        {0, 3},
        {0, 0},
        {0, 10},
        {1, 1},
        {2, 1}
    };

    unsigned int num_failed = 0;
    for (int i = 0; i < sizeof(arr)/sizeof(test_data); ++i) {
        printf("x = %d\n", arr[i].x);
        unsigned rotated = right_rotate(arr[i].x, arr[i].n);

        printf("rotated = %u\n", rotated); 
        
        char original_bits[UNSIGNED_SIZE + 1] = {'0'};
        fill_unsigned_to_bits(arr[i].x, original_bits);
        printf("x bits = %s\n", original_bits);
        
        right_rotate_bits_array(original_bits, arr[i].n);
        printf("rotated bits = %s\n", original_bits);
        
        unsigned rotated_bits_result = convert_bits_to_unsigned(original_bits);
        printf("rotated bits result = %u\n", rotated_bits_result);
        
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
