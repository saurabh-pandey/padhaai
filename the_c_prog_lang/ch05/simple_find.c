#include <stdio.h>
#include <string.h>


// -----------------------------------------------------
// Read the lines
// -----------------------------------------------------

#define MAX_LINES 100
#define MAX_LEN 100


int get_line(char * line, int max_len) {
    char c;
    int n_chars = 0;
    while((c = getchar()) != EOF) {
        if (c == '\n') {
            line[n_chars] = '\0';
            return ++n_chars;
        } else {
            line[n_chars] = c;
            ++n_chars;
        }
    }
    return EOF;
}

int main(int argc, char *argv[]) {
    for (int i = 0; i < argc; ++i) {
        printf("Arg %d => %s\n", i, argv[i]);
    }

    return 0;
}
