#include <stdio.h>

int main() {
    long count = 0;
    while (getchar() != EOF) {
        ++count;
    }
    printf("Total number of characters = %ld\n", count);
    
    return 0;
}
