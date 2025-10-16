#include <stdio.h>

#include "fsize.h"


int main(int argc, char * argv[]) {
    printf("Running fsize program\n");

    if (argc == 1) {
        fsize(".");
    } else {
        for (int i = 1; i < argc; ++i) {
            fsize(argv[i]);
        }
    }

    return 0;
}
