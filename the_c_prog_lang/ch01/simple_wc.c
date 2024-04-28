#include <stdio.h>

int main() {
    long nchar = 0;
    long nword = 0;
    long nline = 0;

    int c = 0;
    int in_word = 0;
    while ((c = getchar()) != EOF) {
        // Count every character
        ++nchar;
        // Count new-lines as lines
        if (c == '\n') {
            ++nline;
        }
        // Space, tab and new-line is considered as end of word. Everything else is a beginning.
        if (c == ' ' || c == '\t' || c == '\n') {
            if (in_word == 1) {
                ++nword;
            }
            in_word = 0;
        } else {
            in_word = 1;
        }
    }

    printf("Number of characters = %ld, words = %ld and lines = %ld\n", nchar, nword, nline);

    return 0;
}
