#include <stdio.h>
#include <ctype.h>

#define MAX_ARR_SZ 10

int getint(int *pn) {
    static int buffer = 0;
    int sign = 0;
    int c = buffer == 0 ? getchar() : buffer;
    buffer = 0;

    // Keep looping until we are sure we have arrived at something that is a number. This means we 
    // ignore everything other than digits, sign and EOF. If a sign is not immediately followed by 
    // a digit then it is ignored. For eg. "-2" is -2 but "- 2" is just 2 and "- a" is not a number
    while (1) {
        // If it is a digit we are done. We parse this and potentially subsequent digits later
        if (isdigit(c)) {
            break;
        }
        // Reached EOF so that's all folks
        if (c == EOF) {
            return EOF;
        }

        // Reset the sign value here. This handles the case where sign is followed by anything 
        // other than a digit. If sign was followed by a digit it would already be captured above
        // with the correct sign value. So if we are here that means we are looking a fresh
        sign = 0;

        // Check for sign
        if (c == '+') {
            sign = 1;
        }
        if (c == '-') {
            sign = -1;
        }

        // Fetch next char
        c = getchar();
    }

    // If we are here then we are indeed looking at a number. Now if sign was not set that means 
    // sign was never provided in the input. This in turn means that sign is 1.
    sign = sign == 0 ? 1 : sign;

    // Now we parse all the digits
    for (*pn = 0; isdigit(c); c = getchar()) {
        *pn = (*pn) * 10 + (c - '0');
    }

    // Here we have read a character extra that is certainly not a digit. But if it is a sign or 
    // EOF then we will need to consider this char in the next call. Thus we buffer it for now.
    buffer = c;

    // Fix the sign
    *pn *= sign;

    // Return c to capture the EOF for someone to track and exit the loop
    return c;
}


int main() {
    int array[MAX_ARR_SZ] = {0};
    
    for (int i = 0; (i < MAX_ARR_SZ) && (getint(&array[i]) != EOF); ++i) {
        if (i == MAX_ARR_SZ - 1) {
            printf("Array has reached max size = %d\nExiting.\n", MAX_ARR_SZ);
        }
    }

    // Print the array parsed
    printf("arr = [");
    for (int i = 0; i < MAX_ARR_SZ; ++i) {
        printf("%d", array[i]);
        if (i != (MAX_ARR_SZ - 1)) {
            printf(", ");
        }
    }
    printf("]\n");
    
    return 0;
}
