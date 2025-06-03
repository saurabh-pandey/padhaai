#include <stdio.h>
#include <string.h>

#define MAX_LINES 100
#define MAX_LEN 100


int get_line(char * line, int max_len) {
    char c;
    int n_chars = 0;
    while((c = getchar()) != EOF) {
        if (c == '\n') {
            line[n_chars] = '\0';
            return ++n_chars;
        } else {
            line[n_chars] = c;
            ++n_chars;
        }
    }
    return EOF;
}


// A stack like growing and shrinking memory pool
#define MAX_POOL_SIZE 10000

static char mem_pool[MAX_POOL_SIZE] = "";
static char * pool_ptr = mem_pool;

char * my_alloc(int len) {
    // Return the free space from above pool
    if (mem_pool + MAX_POOL_SIZE - pool_ptr >= len) {
        char * orig_pool_ptr = pool_ptr;
        pool_ptr += len;
        return orig_pool_ptr;
    }
    // TODO: error here
    return NULL;
}

void my_dealloc(int len) {
    // Free this data
}


int read_lines(char *lines[], int max_lines) {
    int n_lines = 0;
    char a_line[MAX_LEN] = "";
    int len_line = 0;
    while ((len_line = get_line(a_line, MAX_LEN)) != EOF) {
        printf("a line = %s\n", a_line);
        lines[n_lines] = my_alloc(len_line);
        printf("Line %d ptr = %p\n", n_lines, lines[n_lines]);
        strcpy(lines[n_lines], a_line);
        printf("Line %d ptr = %s\n", n_lines, lines[n_lines]);
        ++n_lines;
    }

    return n_lines;
}

void write_lines(char *lines[], int n_lines) {
    for (int i = 0; i < n_lines; ++i) {
        printf("Line no %d: %s\n", i, lines[i]);
    }
}

void qsort(char *lines[], int left, int right) {}

int main(int argc, char *argv[]) {
    // if (argc < 2) {
    //     printf("\nUsage:\n");
    //     printf("   ./bin/simple_sort\n");
    //     printf("\n");
    //     return 0;
    // }

    int n_lines = 0;
    char *lines[MAX_LINES] = {};

    if ((n_lines = read_lines(lines, MAX_LINES)) > 0) {
        // qsort(lines, 0, n_lines - 1);
        write_lines(lines, n_lines);
        return 0;
    } else {
        printf("Error while reading lines\n");
        return 1;
    }

    return 0;
}
