#include <stdio.h>

#define IN 1
#define OUT 0

int main() {
    long nchar = 0;
    long nword = 0;
    long nline = 0;

    int c = 0;
    int status = OUT;
    while ((c = getchar()) != EOF) {
        // Count every character
        ++nchar;
        // Count new-lines as lines
        if (c == '\n') {
            ++nline;
        }
        // Space, tab and new-line is considered as end of word. Everything else is a beginning.
        if (c == ' ' || c == '\t' || c == '\n') {
            if (status == IN) {
                ++nword;
            }
            status = OUT;
        } else {
            status = IN;
        }
    }

    printf("Number of characters = %ld, words = %ld and lines = %ld\n", nchar, nword, nline);

    return 0;
}
