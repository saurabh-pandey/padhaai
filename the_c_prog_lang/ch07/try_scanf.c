#include <stdio.h>

void try_int(void) {
    int num = 0;

    printf("Enter an int: ");
    scanf("%d", &num);
    printf("int entered is = %d\n", num);
}

void try_double(void) {
    double num = 0;

    printf("Enter a double: ");
    scanf("%lf", &num);
    printf("double entered is = %f\n", num);
}

void try_string(void) {
    char str[20];

    printf("Enter a string: ");
    scanf("%s", str);
    printf("String entered is = %s\n", str);
}

int main() {
    printf("Running tests for try_scanf\n");

    try_int();
    try_double();
    try_string();

    printf("Done\n");
    
    return 0;
}