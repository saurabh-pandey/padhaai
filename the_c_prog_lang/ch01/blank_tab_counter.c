#include <stdio.h>

int main() {
    long nblank = 0;
    long ntab = 0;
    int c = 0;
    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            ++nblank;
        } else if (c == '\t') {
            ++ntab;
        }
    }
    printf("Number of tabs = %ld and blank = %ld\n", ntab, nblank);
    
    return 0;
}
