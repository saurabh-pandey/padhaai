#include <stdio.h>
#include <stdbool.h>


#define MAX_PATTERN_LIMIT 20
#define MAX_LINE_LIMIT 100


int get_line(char line[], int max_line_size) {
    int len = 0;
    int c = 0;
    while((c = getchar()) != EOF) {
        if (c == '\n') {
            line[len] = '\n';
            ++len;
            break;
        }
        if (len == (MAX_LINE_LIMIT - 2)) {
            break;
        }
        line[len] = c;
        ++len;
    }
    line[len] = '\0';
    return len;
}

bool is_pattern_found(char line[], char pattern[]) {
    int j = 0;
    for (int i = 0; line[i] != '\0'; ++i) {
        if (pattern[j] != line[i]) {
            // If pattern doesn't match reset
            j = 0;
        } else {
            // Continue if we match the pattern
            ++j;
        }
        // If reached the end it's a match
        if (pattern[j] == '\0') {
            return true;
        }
    }
    return false;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        printf("\nUsage:\n");
        printf("   ./bin/simple_pattern_search <pattern>\n\n");
        return 0;
    }

    char pattern[MAX_PATTERN_LIMIT];
    int i = 0;
    while(argv[1][i] != '\0' && i < (MAX_PATTERN_LIMIT - 1)) {
        pattern[i] = argv[1][i];
        ++i;
    }
    pattern[i] = '\0';
    char line[MAX_LINE_LIMIT] = "";

    while (get_line(line, MAX_LINE_LIMIT) > 0) {
        if (is_pattern_found(line, pattern)) {
            printf("%s", line);
        }
    }

    return 0;
}
