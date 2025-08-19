#include <stdio.h>
#include <unistd.h>

int unbuf_getchar() {
    char c;
    ssize_t n = read(0, &c, 1);
    return n == 1 ? (unsigned int)c : EOF;
}

int main() {
    char c;
    while ((c = unbuf_getchar()) != EOF) {
        printf("%c", c);
    }

    return 0;
}
