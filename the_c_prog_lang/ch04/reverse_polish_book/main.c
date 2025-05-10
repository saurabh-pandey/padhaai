#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "parser.h"
#include "stack.h"


#define MAX_INP 20
#define EPSILON 1.0e-06


int check_stack(int min_expected_size) {
    if (size() < min_expected_size) {
        printf("WARNING: Min stack size = %d. Stack status:\n", min_expected_size);
        print();
        printf("Clearing the stack\n");
        clear();
        return 0;
    }
    return 1;
}


int main() {
    // Controls when to show the prompt
    int prompt = 1;
    Token token = INVALID;
    char parsed_inp[MAX_INP] = "\0";
    while(1) {
        if (prompt == 1) {
            printf("expr> ");
            prompt = 0;
        }
        
        token = getop(parsed_inp);
        switch (token)
        {
            case NUMBER:
            {
                double const num = atof(parsed_inp);
                push(num);
                break;
            }
            case OP:
            {
                switch (parsed_inp[0])
                {
                    case '+':
                    {
                        if (check_stack(2) != 0) {
                            const double num2 = pop();
                            const double num1 = pop();
                            push(num1 + num2);
                        }
                        break;
                    }
                    case '-':
                    {
                        if (check_stack(2) != 0) {
                            const double num2 = pop();
                            const double num1 = pop();
                            push(num1 - num2);
                        }
                        break;
                    }
                    case '*':
                    {
                        if (check_stack(2) != 0) {
                            const double num2 = pop();
                            const double num1 = pop();
                            push(num1 * num2);
                        }
                        break;
                    }
                    case '/':
                    {
                        if (check_stack(2) != 0) {
                            const double num2 = pop();
                            if (fabs(num2) < EPSILON) {
                                printf("ERROR: Division by zero is not allowed\n");
                                break;
                            }
                            const double num1 = pop();
                            push(num1 / num2);
                        }
                        break;
                    }
                    case '\n':
                    {
                        if (size() != 1) {
                            printf("WARNING: Expected the stack to contain only one element here. Stack status:\n");
                            print();
                            printf("Clearing the stack\n");
                            clear();
                        } else {
                            printf("Result = %f\n", pop());
                        }
                        prompt = 1;
                        break;
                    }
                    default:
                    {
                        printf("ERROR: Unknown operator %s\n", parsed_inp);
                        break;
                    }
                }
                break;
            }
            case INVALID:
            {
                printf("ERROR: Invalid input\n");
                return -1;
            }
            default:
            {
                printf("DONE %s\n", parsed_inp);
                return 0;
            }
        }
    }
    return 0;
}
