#include <ctype.h>
#include <stdio.h>

#define MAX_INP 20

int getop(char parsed_inp[]) {
    int c = 0;
    // Skip all whitespace char in the beginning
    while((c = getchar()) != EOF) {
        if (c == ' ' || c == '\t') {
            continue;
        } else {
            break;
        }
    }

    // c = getchar();
    if (c == EOF) {
        return -1;
    }
    
    // Parse for op
    parsed_inp[1] = '\0';
    if (c != '.' && !isdigit(c)) {
        parsed_inp[0] = c;
        return 0;
    }
    
    // Parse for number
    int i = 0;
    parsed_inp[i] = c;
    ++i;
    while ((c = getchar()) != EOF) {
        if (isdigit(c)) {
            parsed_inp[i] = c;
        } else if (c == '.') {
            parsed_inp[i] = c;
        } else {
            break;
        }
        ++i;
    }
    parsed_inp[i] = '\0';
    return 0;
}

int main() {
    int ret_val = 0;
    char parsed_inp[MAX_INP] = "\0";
    while((ret_val = getop(parsed_inp)) != -1) {
        printf("<=> %s\n", parsed_inp);
    }
    return 0;
}
