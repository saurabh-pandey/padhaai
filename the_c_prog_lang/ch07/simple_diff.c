#include <stdio.h>
#include <unistd.h>
#include <linux/limits.h>


int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "ERROR: %s need 2 files for diff\n", argv[0]);
    } else {
        FILE *file1 = fopen(argv[1], "r");
        if (file1 == NULL) {
            fprintf(stderr, "ERROR: %s Can't open file %s\n", argv[1]);
        }
        FILE *file2 = fopen(argv[2], "r");
        if (file2 == NULL) {
            fprintf(stderr, "ERROR: %s Can't open file %s\n", argv[2]);
        }
        
        while (0) {
            // read line in each file
            // compare
            // if diff print
            // break if EOF of both files reached
        }
        
    }
    return 0;
}