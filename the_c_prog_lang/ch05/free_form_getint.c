#include <stdio.h>
#include <ctype.h>

static int buffer = 0;

int getch() {
    int c = 0;
    if (buffer == 0) {
        c = getchar();
    } else {
        c = buffer;
        buffer = 0;
    }
    return c;
}


int getint(int *pn) {
    static int buffer = 0;
    int sign = 0;
    int c = buffer == 0 ? getchar() : buffer;
    buffer = 0;

    // Ignore all white spaces
    while (isspace(c = getch())) {}

    // Check all the characters we handle later
    if (!isdigit(c) && c != '+' && c != '-' && c != EOF) {
        return 0;
    }

    sign = c == '-' ? -1 : 1;

    if (c == EOF) {
        return c;
    }

    if (c == '+' || c == '-') {
        c = getchar();
    }

    if (isdigit(c)) {
        *pn = (*pn) * 10 + (c - '0');
    }

    if (c != EOF) {
        buffer = c;
    }

    *pn *= sign;
}


int main() {
    int c = 0;
    
    while ((c = getchar()) != EOF) {
        printf("c = %c\n", c);
    }
    
    return 0;
}
