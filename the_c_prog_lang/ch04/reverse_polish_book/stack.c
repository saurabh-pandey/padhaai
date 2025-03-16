#include "stack.h"

#include <stdio.h>


#define MAX_STACK_SIZE 20


double data[MAX_STACK_SIZE];
int stack_ptr = 0;


void push(double num) {
    if (stack_ptr == MAX_STACK_SIZE) {
        printf("ERROR: Stack is full\n");
        return;
    }
    data[stack_ptr++] = num;
}

double pop() {
    if (stack_ptr == 0) {
        printf("ERROR: Stack is empty\n");
        return -1.0;
    }
    return data[--stack_ptr];
}

int size() {
    return stack_ptr;
}
