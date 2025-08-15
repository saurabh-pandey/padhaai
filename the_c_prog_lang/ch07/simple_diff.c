#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/limits.h>


int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "ERROR: %s need 2 files for diff\n", argv[0]);
    } else {
        FILE *file1 = fopen(argv[1], "r");
        if (file1 == NULL) {
            fprintf(stderr, "ERROR: %s Can't open file %s\n", argv[0], argv[1]);
            exit(1);
        }
        FILE *file2 = fopen(argv[2], "r");
        if (file2 == NULL) {
            fprintf(stderr, "ERROR: %s Can't open file %s\n", argv[0], argv[2]);
            exit(1);
        }
        
        while (1) {
            // read line in each file
            char line1[100];
            int is_file1_eof = 0;
            if ((is_file1_eof == 0) && (fgets(line1, 100, file1) != NULL)) {
                printf("Line1: %s\n", line1);
            } else {
                is_file1_eof = 1;
            }

            char line2[100];
            int is_file2_eof = 0;
            if ((is_file2_eof == 0) && (fgets(line2, 100, file2) != NULL)) {
                printf("Line2: %s\n", line2);
            } else {
                is_file2_eof = 1;
            }

            // compare
            // if diff print

            // Break if both files are EOF
            if (is_file1_eof && is_file2_eof) {
                break;
            }
        }
        
        fclose(file1);
        fclose(file2);
        
    }
    return 0;
}