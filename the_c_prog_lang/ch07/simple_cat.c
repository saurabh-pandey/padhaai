#include <stdio.h>

int main(int argc, char *argv[]) {
    printf("Running simple_cat\n");

    FILE *fp;
    if ((fp = fopen("tests/data/text1.txt", "r")) != NULL) {
        int c = 0;
        while ((c = getc(fp)) != EOF) {
            putc(c, stdout);
        }
    } else {
        printf("ERROR: fp is null\n");
    }

    printf("Done\n");
    return 0;
}