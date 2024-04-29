#include <stdio.h>

int main() {
    long ndigit[10] = {0};
    long nwhite = 0;
    long nother = 0;

    int c = 0;
    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\t' || c == '\n') {
            ++nwhite;
        } else if (c >= '0' && c <= '9') {
            ++ndigit[c - '0'];
        } else {
            ++nother;
        }
    }

    printf("Number of whitespaces = %ld\n", nwhite);
    for (int i = 0; i < 10; ++i) {
        printf("Number of %d = %ld\n", i, ndigit[i]);
    }
    printf("Number of other = %ld\n", nother);

    return 0;
}
