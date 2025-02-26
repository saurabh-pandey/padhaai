#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>


#define MAX_STACK_SIZE 100


// Array backed Stack DS with push and pop
double stack[MAX_STACK_SIZE];
int stack_size = 0;

void push(double num) {
    if (stack_size == MAX_STACK_SIZE) {
        printf("ERROR: Max stack size reached so can't push to it.\n");
    }
    stack[stack_size] = num;
    ++stack_size;
}

double pop() {
    if (stack_size == 0) {
        printf("ERROR: Stack is empty so can't pop\n");
    }
    --stack_size;
    return stack[stack_size];
}


// RPN calculator
int main(int argc, char * const argv[]) {
    if (argc < 2) {
        printf("\nUsage:\n");
        printf("   ./bin/reverse_polish_calc <some_calculation>\n");
        printf("   Some examples are:\n");
        printf("     ./bin/reverse_polish_calc 1 2 +\n");
        printf("     ./bin/reverse_polish_calc 1 2 - 4 5 + \'*\'\n");
        printf("\n");
        return 0;
    }

    // Skip the command itself so start from 1
    for (int i = 1; i < argc; ++i) {
        // Check if the first char is digit or -digit
        if (isdigit(argv[i][0]) || (argv[i][0] == '-' && isdigit(argv[i][1]))) {
            const double num = atof(argv[i]);
            push(num);
        } else {
            switch (argv[i][0])
            {
                case '+':
                {
                    const double num2 = pop();
                    const double num1 = pop();
                    push(num1 + num2);
                    break;
                }
                case '-':
                {
                    const double num2 = pop();
                    const double num1 = pop();
                    push(num1 - num2);
                    break;
                }
                case '*':
                {
                    const double num2 = pop();
                    const double num1 = pop();
                    push(num1 * num2);
                    break;
                }
                case '/':
                {
                    const double num2 = pop();
                    if (num2 == 0) {
                        printf("ERROR: Division by zero");
                        return 1;
                    }
                    const double num1 = pop();
                    push(num1 / num2);
                    break;
                }
                default:
                {
                    // Ignore everything else
                    break;
                }
            }
        }
    }
    const double result = pop();
    if (stack_size > 0) {
        printf("WARNING: Stack is not empty (size is %d) at the end of RPN expression evaluation\n",
               stack_size);
    }
    printf("Result = %f\n", result);

    return 0;
}
