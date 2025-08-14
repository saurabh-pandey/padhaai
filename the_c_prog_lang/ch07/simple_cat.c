#include <stdio.h>
#include <unistd.h>
#include <linux/limits.h>


void filecopy(FILE *in, FILE *out) {
    int c = 0;
    while ((c = getc(in)) != EOF) {
        putc(c, out);
    }
    // Print a newline after the EOF
    putc('\n', out);
}


int main(int argc, char *argv[]) {
    if (argc == 1) {
        filecopy(stdin, stdout);
    } else {
        for (int i = 1; i < argc; ++i) {
            FILE *fp;
            if ((fp = fopen(argv[i], "r")) != NULL) {
                filecopy(fp, stdout);
            } else {
                fprintf(stderr, "ERROR: Can't open file %s\n", argv[i]);
            }
        }
    }
    return 0;
}