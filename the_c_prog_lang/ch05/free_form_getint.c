#include <stdio.h>
#include <ctype.h>


int getint(int *pn) {
    static int buffer = 0;
    int sign = 0;
    int c = buffer == 0 ? getchar() : buffer;
    buffer = 0;

    // Ignore all white spaces
    while (isspace(c)) {
        c = getchar();
    }

    // Check all the characters we handle later
    if (!isdigit(c) && c != '+' && c != '-' && c != EOF) {
        return 0;
    }

    // Now c is either digit, sign or EOF
    sign = c == '-' ? -1 : 1;

    // If it is sign then we read the next number
    if (c == '+' || c == '-') {
        c = getchar();
    }

    // Now we parse all the digits
    for (*pn = 0; isdigit(c); c = getchar()) {
        *pn = (*pn) * 10 + (c - '0');
    }

    buffer = c;

    if (c != EOF) {
        buffer = 0;
    }

    *pn *= sign;

    return c;
}


int main() {
    int array[10] = {0};
    
    for (int i = 0; i < 10 && getint(&array[i]) != EOF; ++i) {}

    for (int i = 0; i < 10; ++i) {
        printf("arr[%d] = %d\n", i, array[i]);
    }
    
    return 0;
}
