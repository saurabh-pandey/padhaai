#include <stdio.h>
#include <string.h>


// -----------------------------------------------------
// A stack like growing and shrinking memory pool
// -----------------------------------------------------

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


// -----------------------------------------------------
// Read and sort the lines
// -----------------------------------------------------

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


int read_lines(char *lines[], int max_lines) {
    int n_lines = 0;
    char a_line[MAX_LEN] = "";
    int len_line = 0;
    while ((len_line = get_line(a_line, MAX_LEN)) != EOF) {
        lines[n_lines] = my_alloc(len_line);
        strcpy(lines[n_lines], a_line);
        ++n_lines;
    }

    return n_lines;
}

void write_lines(char *lines[], int n_lines) {
    printf("Sorted output:\n");
    for (int i = 0; i < n_lines; ++i) {
        printf("%s\n", i, lines[i]);
    }
}


void swap(char *lines[], int i, int j) {
    char *temp = lines[i];
    lines[i] = lines[j];
    lines[j] = temp;
}


// NOTE: left and right args are assumed to be inclusive
void qsort(char *lines[], int left, int right) {
    // Input array of size 1 or less is already sorted
    if (left >= right) {
        return;
    }

    // Input array is of size > 1
    const int pivot = (left + right) / 2;

    // Move pivot to the start of the array
    swap(lines, left, pivot);

    // Partition around pivot
    int partition_index = left;
    for (int i = left + 1; i <= right; ++i) {
        if (strcmp(lines[i], lines[left]) < 0) {
            // This element should be moved to the left of partition_index
            ++partition_index;
            swap(lines, i, partition_index);
        }
    }
    swap(lines, left, partition_index);
    
    // Recurse on the left and right of partitioned subarrays
    qsort(lines, left, partition_index - 1);
    qsort(lines, partition_index + 1, right);
}

int main(int argc, char *argv[]) {
    printf("Input some lines below to sort:\n");

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
