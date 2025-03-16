#include <stdio.h>

#include "parser.h"


#define MAX_INP 20


int main() {
    int ret_val = 0;
    char parsed_inp[MAX_INP] = "\0";
    while(1) {
        ret_val = getop(parsed_inp);
        switch (ret_val)
        {
            case NUMBER:
                // TODO: Check if it is indeed a number and push to stack
            case OP:
                // TODO: Check if it is a valid option and eval
            case NEW_LINE:
                // TODO: Is this where we print the outcome?
                printf("<=> %s\n", parsed_inp);
                break;
            case INVALID:
                printf("ERROR: Invalid input\n");
                return -1;
            default:
                printf("<=> DONE %s\n", parsed_inp);
                return 0;
        }
    }
    return 0;
}
