#include <stdio.h>
#include <unistd.h>

// #define EOF -1

int my_getchar() {
    char c;
    ssize_t n = read(0, &c, 1);
    return n == 1 ? (unsigned int)c : EOF;
}

int main() {
    char c;
    while ((c = my_getchar()) != EOF) {
        printf("%c", c);
    }

    return 0;
}
