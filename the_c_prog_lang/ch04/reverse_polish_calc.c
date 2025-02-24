#include <stdio.h>

#define MAX_STACK_SIZE 100


int stack[MAX_STACK_SIZE];
int stack_index = 0;

void push(int num) {
    if (stack_index == MAX_STACK_SIZE) {
        printf("Error: Stack overflow\n");
    }
    stack[stack_index] = num;
    ++stack_index;
}

int pop() {
    if (stack_index == 0) {
        printf("Error: Stack is empty\n");
    }
    --stack_index;
    return stack[stack_index];
}


int main(int argc, char * const argv[]) {
    // if (argc < 2) {
    //     printf("\nUsage:\n");
    //     printf("   ./bin/reverse_polish_calc <some_calculation>\n");
    //     printf("   Some examples are:\n");
    //     printf("     ./bin/reverse_polish_calc 1 2 +\n");
    //     printf("     ./bin/reverse_polish_calc 1 2 - 4 5 + *\n");
    //     printf("\n");
    //     return 0;
    // }

    int c = 0;
    while ((c = getchar()) != EOF) {
        if (c >= '0' && c <= '9') {
            push(c - '0');
        } else {
            switch (c)
            {
                case '+':
                {
                    const int num2 = pop();
                    const int num1 = pop();
                    push(num1 + num2);
                    break;
                }
                case '-':
                {
                    const int num2 = pop();
                    const int num1 = pop();
                    push(num1 - num2);
                    break;
                }
                case '*':
                {
                    const int num2 = pop();
                    const int num1 = pop();
                    push(num1 * num2);
                    break;
                }
                case '/':
                {
                    const int num2 = pop();
                    if (num2 == 0) {
                        printf("ERROR: Division by zero");
                        return 1;
                    }
                    const int num1 = pop();
                    push(num1 / num2);
                    break;
                }
                case '\n':
                {
                    const int result = pop();
                    // TODO: A check here that the stack is empty might be useful
                    printf("Result = %d\n", result);
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

    return 0;
}
