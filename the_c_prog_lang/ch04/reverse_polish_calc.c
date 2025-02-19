#include <stdio.h>


int main(int argc, char * const argv[]) {
    if (argc < 2) {
        printf("\nUsage:\n");
        printf("   ./bin/reverse_polish_calc <some_calculation>\n");
        printf("   Some examples are:\n");
        printf("     ./bin/reverse_polish_calc 1 2 +\n");
        printf("     ./bin/reverse_polish_calc 1 2 - 4 5 + *\n");
        printf("\n");
        return 0;
    }

    return 0;
}
