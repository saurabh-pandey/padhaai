#include <stdio.h>

int main() {
    char arr[] = "Hello, character array";
    char *ptr = "Hello, character pointer";

    printf("Initial Char arr = %s\n", arr);

    printf("Initial Char ptr = %s\n", ptr);

    arr[0] = 'h';

    printf("After change char arr = %s\n", arr);

    // Will cause seg fault!!!
    // ptr[0] = 'h';

    return 0;
}