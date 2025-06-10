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
    int except = 0;
    int line_num = 0;
    
    for (int i = 0; i < argc; ++i) {
        printf("Arg %d => %s\n", i, argv[i]);
        if (argv[i][0] == '-') {
            int j = 1;
            while (argv[i][j] != '\0') {
                if (argv[i][j] == 'x') {
                    except = 1;
                }
                else if (argv[i][j] == 'n') {
                    line_num = 1;
                } else {
                    printf("simple_find: illegal option %c\n", argv[i][j]);
                }
                ++j;
            }
        }
    }

    printf("except = %d, line_num = %d\n", except, line_num);

    return 0;
}
