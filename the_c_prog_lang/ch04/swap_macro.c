#include <stdio.h>

#define MAX_NUM 100
#define MIN_NUM -MAX_NUM


#define SWAP(t, a, b) do { \
t temp; \
temp = a; \
a = b; \
b = temp; \
} while(0) \

int main() {
    int a = 2;
    int b = 3;

    printf("Before swap = (%d, %d)\n", a, b);
    SWAP(int, a, b);
    printf("After  swap = (%d, %d)\n", a, b);

    double c = 2.1;
    double d = 3.2;

    printf("Before swap = (%f, %f)\n", c, d);
    SWAP(double, c, d);
    printf("After swap = (%f, %f)\n", c, d);

    return 0;
}
