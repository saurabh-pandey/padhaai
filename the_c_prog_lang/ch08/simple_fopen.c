#include <stdio.h>

#include <fcntl.h> // open(), creat()
#include <unistd.h> // close()


#define MAX_FILES 5
#define MAX_CHAR_ARR_SIZE 100
#define BUFFER_SIZE 100


#define FILL_ARRAY(arr, val) do {               \
    size_t _n = sizeof(arr)/sizeof((arr)[0]);   \
    for (size_t _i = 0; _i < _n; _i++) {        \
        (arr)[_i] = (val);                      \
    }                                           \
} while (0)



typedef struct MY_FILE {
    int fd; // File descriptor
    char buf[BUFFER_SIZE]; // Buffer
    char *curr; // Read pointer to buffer
    size_t count; // Amount of buffer still unread
} MY_FILE;

MY_FILE file_table[MAX_FILES];

void print_my_file(MY_FILE *f) {
    if (f == NULL) {
        printf("NULL");
    }
    printf("{%d, %s, %s, %ld}", f->fd, f->buf, f->curr, f->count);
}

void print_file_table(const char*prefix) {
    printf("%s: File table\n", prefix);
    for (int i = 0; i < MAX_FILES; ++i) {
        printf("%d => ", (i + 1));
        print_my_file(&(file_table[i]));
        printf("\n");
    }
}


MY_FILE *fetch_first_free_file_from_table() {
    for (int i = 0; i < MAX_FILES; ++i) {
        MY_FILE *curr_f = &(file_table[i]);
        if (curr_f->fd == -1) {
            return curr_f;
        }
    }
    return NULL;
}

size_t fill_used_files(MY_FILE *used_fds[]) {
    size_t total_used_files = 0;
    for (int i = 0; i < MAX_FILES; ++i) {
        MY_FILE *curr_f = &(file_table[i]);
        if (curr_f->fd != -1) {
            used_fds[total_used_files] = curr_f;
            ++total_used_files;
        }
    }
    return total_used_files;
}


size_t fill_used_fds(int *used_fds) {
    size_t total_used_fds = 0;
    for (int i = 0; i < MAX_FILES; ++i) {
        MY_FILE *curr_f = &(file_table[i]);
        if (curr_f->fd != -1) {
            used_fds[total_used_fds] = curr_f->fd;
            ++total_used_fds;
        }
    }
    return total_used_fds;
}


size_t count_open_fds() {
    size_t total_used_fds = 0;
    for (int i = 0; i < MAX_FILES; ++i) {
        if (file_table[i].fd != -1) {
            ++total_used_fds;
        }
    }
    return total_used_fds;
}


MY_FILE *my_fopen(const char *pathname, const char *mode) {
    // printf("Calling my_fopen for path = %s, mode = %s\n", pathname, mode);

    switch (*mode)
    {
        case 'r':
        {
            // Read mode
            const int fd = open(pathname, O_RDONLY);
            if (fd == -1) {
                // char msg_prefix[MAX_CHAR_ARR_SIZE];
                // snprintf(msg_prefix, sizeof(msg_prefix), "ERROR while opening file%s", pathname);
                // perror(msg_prefix);
                // exit(1);
                return NULL;
            }
            MY_FILE *f = fetch_first_free_file_from_table();
            if (f == NULL) {
                printf("ERROR: Seems like file table is full\n");
                return NULL;
            }
            f->fd = fd;
            f->buf[0] = '\0';
            // TODO: Is this correct or shall curr be assigned to buf?
            f->curr = NULL;
            f->count = 0;
            return f;
            break;
        }
        case 'w':
        {
            // Write mode
            break;
        }
        case 'a':
        {
            // Append mode
            break;
        }
    
        default:
            break;
    }
    return NULL;
}

int my_fgetc(MY_FILE *stream) {
    int c;
    int nread = 0;
    while ((nread = read(stream->fd, &c, 1)) > 0)
    {
        printf("%c", c);
    }
    printf("\n");
    return nread;
}

int my_fclose(MY_FILE *stream) {
    if (stream == NULL) {
        printf("WARNING: NULL file stream can't be closed\n");
        return -1;
    }
    
    int found = 0;
    for (int i = 0; i < MAX_FILES; ++i) {
        if (stream == &(file_table[i])) {
            found = 1;
            break;
        }
    }

    if (found == 0) {
        printf("ERROR: File stream is not found in the file table\n");
        return -1;
    }

    // Free this table entry
    const int fd = stream->fd;
    stream->fd = -1;
    // TODO: Might do some cleanup of other members of the file ptr
    
    // printf("Closing file with fd = %d\n", fd);
    return close(fd);
}


// Test functions
#define NUM_FILES_WITHIN_LIMITS 3

int check_fd_count(int expected) {
    int actual = -1;
    if ((actual = count_open_fds()) != expected) {
        printf("ERROR: Expected open fds to be %d but actual is %d\n", expected, actual);
        return 1;
    }
    return 0;
}

int test_open_close_within_limits(int debug) {
    const char *inp_file_name = "tests/data/input.txt";
    
    if (debug) {
        print_file_table("Beginning");
    }
    
    if (check_fd_count(0) != 0) {
        return 1;
    }
    
    MY_FILE *open_files[NUM_FILES_WITHIN_LIMITS] = {NULL};
    for (int i = 0; i < NUM_FILES_WITHIN_LIMITS; ++i) {
        MY_FILE *f = my_fopen(inp_file_name, "r");
        if (f == NULL) {
            printf("ERROR: Unable to open the file %s\n", inp_file_name);
            return 1;
        } else {
            if (debug) {
                printf("Opened file fd = %d\n", f->fd);
            }
            
            open_files[i] = f;
            
            if (check_fd_count(i + 1) != 0) {
               return 1;
            }
        }
        if (debug) {
            char prefix[BUFFER_SIZE];
            prefix[0] = '\0';
            snprintf(prefix, BUFFER_SIZE, "After opening %d file", (i + 1));
            print_file_table(prefix);
        }
    }
    
    for (int i = 0; i < NUM_FILES_WITHIN_LIMITS; ++i) {
        if (debug) {
            char prefix[BUFFER_SIZE];
            prefix[0] = '\0';
            snprintf(prefix, BUFFER_SIZE, "Before closing %d file", (i + 1));
            print_file_table(prefix);
        }
        
        if (check_fd_count(NUM_FILES_WITHIN_LIMITS - i) != 0) {
            return 1;
        }
        
        my_fclose(open_files[i]);
        
        if (debug) {
            char prefix[BUFFER_SIZE];
            prefix[0] = '\0';
            snprintf(prefix, BUFFER_SIZE, "After closing %d file", (i + 1));
            print_file_table(prefix);
        }

        if (check_fd_count(NUM_FILES_WITHIN_LIMITS - i - 1) != 0) {
            return 1;
        }
    }

    if (debug) {
        print_file_table("End");
    }

    if (check_fd_count(0) != 0) {
        return 1;
    }

    return 0;
}


int main(int argc, char *argv[]) {
    printf("Trying file ptr\n");

    // Initialize the fd table
    FILL_ARRAY(file_table, ((MY_FILE){-1, "", NULL, 0}));

    int failed = 0;
    // Start all the tests
    if ((failed = test_open_close_within_limits(0)) != 0)
    {
        printf("ERROR: test_open_close_within_limits\n");
    }

    if (failed) {
        printf("ERROR: Failed with some tests\n");
    }

    return 0;
}
