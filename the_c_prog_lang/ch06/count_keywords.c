#include <stdio.h>

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

int main(int argc, char *argv[]) {
    printf("Count all keyword occurrences\n");
    return 0;
}
