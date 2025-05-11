#include <stdio.h>


#define MAX_STR_LEN 20


void recursive_printd(int n) {
    if (n < 0) {
        printf("-");
        n = -n;
    }

    if (n / 10 > 0) {
        recursive_printd(n / 10);
    }
    printf("%c", (n % 10) + '0');
}


int main() {
    printf("Running tests for recursive_printd\n");

    for (int i = -100; i < 101; ++i) {
        recursive_printd(i);
        printf("\n");
    }
    
    printf("Done\n");

    return 0;
}
