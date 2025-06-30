#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LEN 100


int getword(char *word) {
    char c = 0;
    int i = 0;
    while ((c = getchar()) != EOF) {
        if (isalpha(c)) {
            word[i] = c;
            ++i;
        } else {
            word[i] = '\0';
            return i;
        }
    }
    return EOF;
}


int main(int argc, char *argv[]) {
    printf("Count all words\n");
    char word[MAX_WORD_LEN] = "";
    int word_len = 0;
    while ((word_len = getword(word)) != EOF) {
        printf("%s\n", word);
    }

    return 0;
}
