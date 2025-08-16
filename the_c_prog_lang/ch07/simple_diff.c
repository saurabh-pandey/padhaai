#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <linux/limits.h>

#define MAX_LINE_LEN 150


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
        
        int nums_match = 0;
        int nums_mismatch = 0;
        int nums_one_sided = 0;
        int nums_file1_lines = 0;
        int nums_file2_lines = 0;
        while (1) {
            // read line in each file
            char line1[MAX_LINE_LEN];
            int is_file1_eof = 0;
            if ((is_file1_eof == 0) && (fgets(line1, MAX_LINE_LEN, file1) != NULL)) {
                ++nums_file1_lines;
            } else {
                is_file1_eof = 1;
            }

            char line2[MAX_LINE_LEN];
            int is_file2_eof = 0;
            if ((is_file2_eof == 0) && (fgets(line2, MAX_LINE_LEN, file2) != NULL)) {
                ++nums_file2_lines;
            } else {
                is_file2_eof = 1;
            }

            // compare
            if (is_file1_eof == 0 && is_file2_eof == 0) {
                // Both files have lines so compare the lines
                if (strcmp(line1, line2) == 0) {
                   ++nums_match;
                } else {
                    ++nums_mismatch;
                }
            } else if ((is_file1_eof == 1) && (is_file2_eof == 1)) {
                // Break if both files are EOF
                break;
            } else {
                // One file has reached EOF so it is a one-side diff now
                ++nums_one_sided;
            }
        }

        printf("Overall diff statistics:\n");
        printf("No. of lines matching      = %d\n", nums_match);
        printf("No. of lines with diff     = %d\n", nums_mismatch);
        printf("No. of lines only one file = %d\n", nums_one_sided);
        printf("No. of lines file1         = %d\n", nums_file1_lines);
        printf("No. of lines file2         = %d\n", nums_file2_lines);
        
        fclose(file1);
        fclose(file2);
        
    }
    return 0;
}