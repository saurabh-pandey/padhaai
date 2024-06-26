#include <stdio.h>

#define MAX_LINE_LENGTH 1000

int get_line(char *line, int limit);
void copy_from_to(char * from, char * to);

int main() {
    char max_line[MAX_LINE_LENGTH];
    char line[MAX_LINE_LENGTH];
    int max_line_length = 0;
    int line_length = 0;
    while ((line_length = get_line(line, MAX_LINE_LENGTH)) > 0) {
        printf("Line = %s", line);
        printf("length = %d\n", line_length);
        if (line_length > max_line_length) {
            copy_from_to(line, max_line);
            max_line_length = line_length;
        }
    }
    printf("Max line = %s", max_line);
    printf("length = %d\n", max_line_length);
    return 0;
}

int get_line(char *line, int limit) {
    int i = 0;
    int c = 0;
    while(((c = getchar()) != EOF) && (c != '\n') && (i < limit - 1)) {
        line[i] = c;
        ++i;
    }
    if (c == '\n') {
        line[i] = c;
        ++i;
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
