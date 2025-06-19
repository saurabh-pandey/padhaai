#include <stdio.h>

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
    {"volatile", 0},
    {"void", 0},
};


int getword(char *word) {
    return 0;
}

struct keyword * binsearch(struct keyword *left, struct keyword *right, char *word) {
    return NULL;
}


int main(int argc, char *argv[]) {
    printf("Count all keyword occurrences\n");
    char word[MAX_WORD_LEN] = "";

    const int keywords_size = sizeof(keywords) / sizeof(keywords[0]);
    while (getword(word) != EOF) {
        struct keyword *word_found = NULL;
        if ((word_found = binsearch(&keywords[0], &keywords[keywords_size - 1], word)) != NULL) {
            (word_found->count)++;
        }
    }
    
    for (int i = 0; i < keywords_size; ++i) {
        printf("%s -> %d\n", keywords[i].word, keywords[i].count);
    }

    return 0;
}
