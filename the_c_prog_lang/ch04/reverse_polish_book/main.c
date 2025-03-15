#include <ctype.h>
#include <stdio.h>


#define MAX_INP 20
#define MAX_BUFFER 20


typedef enum {
    NUMBER,
    OP,
    NEW_LINE,
    END_OF_FILE,
    INVALID
} Token;


char buffer[MAX_BUFFER];
int buffPt = 0;


Token getop(char parsed_inp[]) {
    // printf("Buffer data = %c, pt = %d\n", buffer[0], buffPt);
    int c = buffPt > 0 ? buffer[--buffPt] : getchar();
    // printf("c = %c, val = %d, pt = %d\n", c, c, buffPt);
    // Skip all whitespace char
    while(1) {
        // printf("1- %c\n", c);
        if (c == ' ' || c == '\t') {
            c = getchar();
            continue;
        } else {
            break;
        }
    }

    // printf("2- %c\n", c);

    if (c == EOF) {
        return END_OF_FILE;
    }
    
    // Parse for op
    parsed_inp[1] = '\0';
    if (c != '.' && !isdigit(c)) {
        // printf("3- %c\n", c);
        parsed_inp[0] = c;
        return OP;
    }
    
    // Parse for number
    int i = 0;
    parsed_inp[i] = c;
    // printf("4- %c\n", c);
    ++i;
    // while ((c = getchar()) != EOF) {
    while (1) {
        c = getchar();
        // printf("5- %c\n", c);
        if (isdigit(c)) {
            parsed_inp[i] = c;
        } else if (c == '.') {
            parsed_inp[i] = c;
        } else {
            parsed_inp[i] = '\0';
            buffer[buffPt++] = c;
            // printf("6- %c\n", c);
            return NUMBER; 
        }
        ++i;
    }

    // printf("7- %c\n", c);
    
    return 0;
}

int main() {
    int ret_val = 0;
    char parsed_inp[MAX_INP] = "\0";
    while(1) {
        ret_val = getop(parsed_inp);
        switch (ret_val)
        {
            case NUMBER:
            case OP:
            case NEW_LINE:
                printf("<=> %s\n", parsed_inp);
                break;
            default:
                printf("<=> DONE %s\n", parsed_inp);
                return 0;
        }
    }
    return 0;
}
