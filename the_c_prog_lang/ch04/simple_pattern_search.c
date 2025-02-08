#include <stdio.h>
#include <stdbool.h>


#define MAX_PATTERN_LIMIT 20
#define MAX_LINE_LIMIT 100


int get_line(char line[], int max_line_size) {
    return -1;
}

bool is_pattern_found(char line[], char pattern[]) {
    return false;
}

int main(int argc, char * const argv[]) {
    printf("argc = %d\n", argc);
    for (int i = 0; i < argc; ++i) {
        printf("%s\n", argv[i]);
    }

    if (argc != 2) {
        printf("\nUsage:\n");
        printf("   ./bin/simple_pattern_search <pattern>\n\n");
        return 0;
    }

    char pattern[MAX_PATTERN_LIMIT];
    char line[MAX_LINE_LIMIT] = "";
    
    while (get_line(line, MAX_LINE_LIMIT) != -1) {
        if (is_pattern_found(line, pattern)) {
            printf("%s", line);
        }
    } 

    return 0;
}
