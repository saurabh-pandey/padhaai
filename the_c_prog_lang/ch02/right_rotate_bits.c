#include <stdio.h>
#include <stdbool.h>


#define SIZE (sizeof(unsigned) * 8)


unsigned right_rotate(unsigned x, int n) {
    return 0;
}


void fill_unsigned_to_bits(unsigned num, char bits[]) {

}


void right_rotate_bits_array(char bits[], int n) {

}


unsigned convert_bits_to_unsigned(char bits[]) {
    return 0;
}


typedef struct test_data {
    unsigned x;
    int n;
} test_data;


int main() {
    bool debug = false;
    
    printf("Running tests for right_rotate_bits\n");

    printf("Res = %lu\n", sizeof(unsigned));
    printf("Sz = %lu\n", SIZE);

    char bits[(sizeof(unsigned) * 8) + 1];
    char more_bits[SIZE + 1];

    int i;
    for (i = 0; i < SIZE; ++i) {
        bits[i] = '0';
        more_bits[i] = '0';
    }
    bits[i] = '\0';
    more_bits[i] = '\0';
    printf("bits = %s and more_bits = %s\n", bits, more_bits);

    return 0;
    
    
    // NOTE: All string are of size SIZE
    test_data arr [] = {
        {0, 3},
        {0, 0},
        {0, 10},
        {1, 1},
    };

    unsigned int num_failed = 0;
    for (int i = 0; i < sizeof(arr)/sizeof(test_data); ++i) {
        unsigned rotated = right_rotate(arr[i].x, arr[i].n); 
        
        char original_bits[12] = "00000000000";
        fill_unsigned_to_bits(arr[i].x, original_bits);
        
        right_rotate_bits_array(original_bits, arr[i].n);
        
        unsigned rotated_bits_result = convert_bits_to_unsigned(original_bits);
        
        if (debug) {
            printf("Input = %d, n = %d, expected = %d and result = %d\n",
                   arr[i].x,
                   arr[i].n,
                   rotated_bits_result,
                   rotated);
        }
        if (rotated_bits_result != rotated) {
            printf("Input = %d, n = %d, expected = %d and result = %d\n",
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
