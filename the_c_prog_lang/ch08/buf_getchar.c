#include <stdio.h>
#include <unistd.h>

#define MAX_BUF_SIZE 100

int buf_getchar() {
    static char buffer[MAX_BUF_SIZE];
    static char *bufp = buffer;
    static ssize_t n = 0;

    // printf("n = %ld\n", n);
    if (n == 0) {
        // printf("Reading again\n");
        n = read(0, buffer, sizeof buffer);
        bufp = buffer;
    }

    if (n == 0) {
        // printf("EOF\n");
        return EOF;
    } else {
        // printf("Using buffer n = %ld\n", n);
        char c = *bufp;
        ++bufp;
        --n;
        return c;
    }
}

int main() {
    char c;
    while ((c = buf_getchar()) != EOF) {
        printf("%c", c);
    }

    return 0;
}
