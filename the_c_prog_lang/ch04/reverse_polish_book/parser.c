#include "parser.h"

#include <ctype.h>
#include <stdio.h>


#define MAX_BUFFER 20


char buffer[MAX_BUFFER];
int buffPt = 0;
// TODO: Might implement this in a new file that manages buffer or cache


Token getop(char parsed_inp[]) {
    int c = buffPt > 0 ? buffer[--buffPt] : getchar();
    // Skip all whitespace char
    while(1) {
        if (c == ' ' || c == '\t') {
            c = getchar();
            continue;
        } else {
            break;
        }
    }

    // If we reached EOF we are done
    if (c == EOF) {
        return END_OF_FILE;
    }
    
    // Parse for op
    parsed_inp[1] = '\0';
    if (c != '.' && !isdigit(c)) {
        parsed_inp[0] = c;
        return OP;
    }
    
    // Parse for number
    int i = 0;
    parsed_inp[i] = c;
    ++i;
    while (1) {
        c = getchar();
        if (isdigit(c)) {
            parsed_inp[i] = c;
        } else if (c == '.') {
            parsed_inp[i] = c;
        } else {
            // Not a number anymore store whatever accumulated so far and return
            parsed_inp[i] = '\0';
            buffer[buffPt++] = c;
            return NUMBER; 
        }
        ++i;
    }
    
    return INVALID;
}
