#include <stdio.h>
#include <string.h>

#define MAX_LINES 100
#define MAX_LEN 100


int read_lines(char *lines[], int max_lines) {
    return 0;
}

void write_lines(char *lines[], int n_lines) {}

void qsort(char *lines[], int left, int right) {}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("\nUsage:\n");
        printf("   ./bin/simple_sort\n");
        printf("\n");
        return 0;
    }

    int n_lines = 0;
    char *lines[MAX_LINES] = {};

    if ((n_lines = read_lines(lines, MAX_LINES)) > 0) {
        qsort(lines, 0, n_lines - 1);
        write_lines(lines, n_lines);
        return 0;
    } else {
        printf("Error while reading lines\n");
        return 1;
    }

    return 0;
}
