#include <stdio.h>

#include "fsize.h"


int main(int argc, char * argv[]) {
    printf("Running fsize program\n");

    if (argc == 1) {
        fsize(".", 0);
    } else {
        for (int i = 1; i < argc; ++i) {
            fsize(argv[i], 0);
        }
    }

    return 0;
}
