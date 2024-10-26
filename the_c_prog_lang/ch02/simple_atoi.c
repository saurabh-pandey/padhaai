#include <math.h>
#include <stdio.h>


// int simple_atoi(const char inp[]) {
//     int i = 0;
//     for (i = 0; inp[i] != '\0'; ++i) {
//         printf("%c, %d\n", inp[i], inp[i]);
//     }
//     printf("Size = %d\n", i);
//     unsigned int size = i;
//     int n = 0;
//     // unsigned pow = 1;
//     for (i = 0; inp[i] != '\0'; ++i) {
//         n += pow(10, (size - i - 1)) * (inp[i] - 48);
//     }
//     return n;
// }

int simple_atoi(const char inp[]) {
    int i = 0;
    int n = 0;
    for (i = 0; inp[i] >= '0' && inp[i] <= '9'; ++i) {
        // printf("%c, %d\n", inp[i], inp[i]);
        n = 10 * n + (inp[i] - '0');
    }
    printf("n = %d\n", n);
    return n;
}


int main() {
    printf("Running tests for simple_atoi\n");

    const int result = simple_atoi("0013");
    printf("Result = %d\n", result);
    if (result == 13) {
        printf("Test 0 passed\n");
    } else {
        printf("Test 0 failed\n");
    }
    printf("Done\n");

    return 0;
}
