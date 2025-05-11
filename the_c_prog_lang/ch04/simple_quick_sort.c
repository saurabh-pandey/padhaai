#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define MAX_ARR_SZ 100
#define MIN_ARR_VAL -500
#define MAX_ARR_VAL 500

void fill_array(int size) {
    srand(time(NULL));

    int counts[4] = {0};
    for (int i = 0; i < size; ++i) {
        int rand_val = rand();
        printf("i = %d, rand = %d\n", i, rand_val);
        int val = MIN_ARR_VAL + (MAX_ARR_VAL - MIN_ARR_VAL + 1) * ((float) rand_val / (float) RAND_MAX);
        if (val == 500) {
            ++counts[0];
        }
        if (rand_val == 1) {
            ++counts[1];
        }
        if (val == -499) {
            ++counts[2];
        }
        if (rand_val == (RAND_MAX - 1)) {
            ++counts[3];
        }
        // printf("i = %d, Val = %d\n", i, val);
    }
    printf("%d, %d, %d, %d\n", counts[0], counts[1], counts[2], counts[3]);
}


int main() {
    printf("Running tests for simple_quick_sort\n");

    fill_array(2000000);

    // int input_array[MAX_ARR_SZ] = {0};

    // for (int size = 1; size < (MAX_ARR_SZ + 1); ++size) {
    //     for (int iteration = 0; iteration < 10; ++iteration) {
    //         fill_array(input_array, size);
    //     }
    // }

    printf("Done\n");

    return 0;
}