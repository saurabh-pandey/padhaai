#include <stdio.h>

#define MAX_LINE_LENGTH 1000

long get_line(char *line) {
    int i = 0;
    int c = 0;
    while((c = getchar()) != EOF) {
        if (c != '\n') {
            line[i] = c;
            ++i;
        } else {
            line[i] = '\0';
            ++i;
            break;
        }
    }
    line[i] = '\0';
    return i;
}

void copy_from_to(char * from, char * to) {
    int i = 0;
    while (from[i] != '\0') {
        to[i] = from[i];
        ++i;
    }
    to[i] = '\0';
}

int main() {
    char max_line[MAX_LINE_LENGTH];
    char line[MAX_LINE_LENGTH];
    long max_line_length = 0;
    long line_length = 0;
    while ((line_length = get_line(line)) > 0) {
        // printf("Line = %s, length = %ld\n", line, line_length);
        if (line_length > max_line_length) {
            copy_from_to(line, max_line);
            max_line_length = line_length;
        }
    }
    printf("Max line = %s, length = %ld\n", max_line, max_line_length);
    return 0;
}
