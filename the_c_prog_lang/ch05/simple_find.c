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
    int number = 0;

    char *pattern = NULL;
    
    for (int i = 1; i < argc; ++i) {
        // printf("Arg %d => %s\n", i, argv[i]);
        if (argv[i][0] == '-') {
            int j = 1;
            while (argv[i][j] != '\0') {
                if (argv[i][j] == 'x') {
                    except = 1;
                }
                else if (argv[i][j] == 'n') {
                    number = 1;
                } else {
                    printf("simple_find: illegal option %c\n", argv[i][j]);
                }
                ++j;
            }
        } else {
            pattern = argv[i];
        }
    }

    // printf("except = %d, line_num = %d, pattern = %s\n", except, number, pattern);

    int line_num = 0;
    char line[MAX_LEN] = "";
    while(get_line(line, MAX_LEN) != EOF) {
        ++line_num;
        // printf("%d: %s\n", line_num, line);
        const char * found = strstr(line, pattern);
        if ((except == 0 && found != NULL) || (except == 1 && found == NULL)) {
            if (number == 1) {
                printf("%d: ", line_num);
            }
            printf("%s\n", line);
        }
    }

    return 0;
}
