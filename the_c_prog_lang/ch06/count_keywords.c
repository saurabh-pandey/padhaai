#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LEN 100


// Alphabetically sorted keywords so that we can do binary search. Just added some of the keywords
struct keyword {
    char *word;
    int count;
} keywords[] = {
    {"auto", 0},
    {"break", 0},
    {"case", 0},
    {"char", 0},
    {"const", 0},
    {"continue", 0},
    {"default", 0},
    {"double", 0},
    {"float", 0},
    {"int", 0},
    {"long", 0},
    {"return", 0},
    {"struct", 0},
    {"unsigned", 0},
    {"void", 0},
    {"volatile", 0}
};


int getword(char *word) {
    char c = 0;
    int i = 0;
    while ((c = getchar()) != EOF) {
        if (isspace(c)) {
            word[i] = '\0';
            return i;
        } else {
            word[i] = c;
            ++i;
        }
    }
    return EOF;
}

struct keyword * binsearch(struct keyword *left, struct keyword *right, char *word) {
    
    if (left > right) {
        return NULL;
    }

    struct keyword *mid = left + (right - left) / 2;

    const int comp = strcmp(word, mid->word);

    if (comp == 0) {
        return mid;
    } else if (comp < 0) {
        return binsearch(left, mid - 1, word);
    } else {
        return binsearch(mid + 1, right, word);
    }

    return NULL;
}


int main(int argc, char *argv[]) {
    printf("Count all keyword occurrences\n");
    const int keywords_size = sizeof(keywords) / sizeof(keywords[0]);
    char word[MAX_WORD_LEN] = "";
    int word_len = 0;
    while ((word_len = getword(word)) != EOF) {
        printf("Word = %s, len = %d\n", word, word_len);
        struct keyword *word_found = NULL;
        if ((word_found = binsearch(&keywords[0], &keywords[keywords_size - 1], word)) != NULL) {
            printf("  Found word = %s\n", word);
            (word_found->count)++;
        }
    }
    
    // for (int i = 0; i < keywords_size; ++i) {
    //     printf("%s -> %d\n", keywords[i].word, keywords[i].count);
    // }

    return 0;
}
