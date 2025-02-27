#include <stdio.h>


int main() {
    int c = 0;
    while((c = getchar()) != EOF) {
        printf("<=> %c", c);
    }
    return 0;
}
