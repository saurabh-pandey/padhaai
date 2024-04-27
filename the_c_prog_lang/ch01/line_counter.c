#include <stdio.h>

int main() {
    long nlines = 0;
    int c = 0;
    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            ++nlines;
        }
    }
    printf("Total number of Lines = %ld\n", nlines);

    return 0;
}
