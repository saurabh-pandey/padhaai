#include <stdio.h>

#include <fcntl.h> // open(), creat()
#include <unistd.h> // close()

#include <stdlib.h> // malloc()


#define MAX_FILES 5
#define MAX_CHAR_ARR_SIZE 100
#define PRINT_BUFFER_SIZE 100
#define READ_BUFFER_SIZE 100
#define WRITE_BUFFER_SIZE 100
#define FILE_CREATE_PERMS 0644


#define FILL_ARRAY(arr, val) do {               \
    size_t _n = sizeof(arr)/sizeof((arr)[0]);   \
    for (size_t _i = 0; _i < _n; _i++) {        \
        (arr)[_i] = (val);                      \
    }                                           \
} while (0)



typedef struct MY_FILE {
    int fd; // File descriptor
    char *buf; // Buffer
    char *curr; // Read pointer to buffer
    size_t count; // Amount of buffer in use
} MY_FILE;

MY_FILE file_table[MAX_FILES];

void print_my_file(MY_FILE *f) {
    if (f == NULL) {
        printf("NULL");
    } else {
        printf("{fd = %d, ", f->fd);
        printf("buf = %s, ", f->buf == NULL ? "NULL" : f->buf);
        printf("curr = %s, ", f->curr == NULL ? "NULL" : f->curr);
        printf("count = %ld}", f->count);
    }
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

MY_FILE *create_file_from_fd(int fd) {
    MY_FILE *f = fetch_first_free_file_from_table();
    if (f == NULL) {
        printf("ERROR: Seems like file table is full\n");
        return NULL;
    }
    f->fd = fd;
    f->buf = NULL;
    f->curr = NULL;
    f->count = 0;
    return f;
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
    switch (*mode)
    {
        case 'r':
        {
            // Read mode
            const int fd = open(pathname, O_RDONLY);
            if (fd == -1) {
                return NULL;
            }
            return create_file_from_fd(fd);
            break;
        }
        case 'w':
        {
            // Write mode
            const int fd = creat(pathname, FILE_CREATE_PERMS);
            if (fd == -1) {
                return NULL;
            }
            return create_file_from_fd(fd);
            break;
        }
        case 'a':
        {
            // Append mode
            int fd = open(pathname, O_WRONLY);
            if (fd == -1) {
                // The file was not found so create one
                fd = creat(pathname, FILE_CREATE_PERMS);
            }
            if (fd == -1) {
                return NULL;
            }
            
            // Move to the end of file
            const off_t ret = lseek(fd, 0, SEEK_END);
            if (ret == -1) {
                printf("Error while moving to the end\n");
                return NULL;
            }
            return create_file_from_fd(fd);
            break;
        }
        default:
        {
            printf("Error: File mode %c not supported\n", *mode);
            break;
        }
    }
    return NULL;
}

int my_fgetc(MY_FILE *stream) {
    if (stream->count == 0) {
        printf("Read now\n");
        if (stream->buf == NULL) {
            if ((stream->buf = (char *)malloc(READ_BUFFER_SIZE)) == NULL) {
                printf("Error: Failed to allocate buffer while reading for fd %d\n", stream->fd);
                return EOF;
            }
        }
        int nread = 0;
        if ((nread = read(stream->fd, stream->buf, READ_BUFFER_SIZE)) < 0) {
            printf("Error: Failed to read from file fd %d\n", stream->fd);
            return EOF;
        }
        stream->count = nread;
        stream->curr = stream->buf;
    }

    if (stream->count == 0) {
        printf("Reached EOF\n");
        return EOF;
    }
    printf("Use buffer now\n");
    int c = *(stream->curr);
    (stream->curr)++;
    (stream->count)--;
    
    return c;
}


int my_fputc(int c, MY_FILE *stream) {
    // TODO: Here I fill the stream struct
    // I can have 2 modes here:
    // 1. Unbuffered mode: Fill 1 character at a time
    // 2. Buffered mode: Fill some "page" at a time

    if (stream->buf == NULL) {
        if ((stream->buf = (char *)malloc(WRITE_BUFFER_SIZE)) == NULL) {
            printf("Error: Failed to allocate buffer while writing for fd %d\n", stream->fd);
            return EOF;
        }
        stream->curr = stream->buf;
    }

    if (c != EOF) {
        printf("Fill buffer now\n");
        *(stream->curr) = (char)c;
        // stream->buf[stream->count] = (char)c;
        // int c = *(stream->curr);
        (stream->curr)++;
        (stream->count)++;
    }

    if ((stream->count == WRITE_BUFFER_SIZE) || (c == '\n') || (c == EOF)) {
        printf("Write now\n");
        const ssize_t nwrite = write(stream->fd, stream->buf, stream->count);
        printf("nwrite = %ld\n", nwrite);
        stream->count = 0;
        stream->curr = stream->buf;
    }
    
    return c;
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

    // TODO: Before cleaning the buffer if it is write or append mode then I should flush it.

    // Free this table entry
    const int fd = stream->fd;
    stream->fd = -1;
    free(stream->buf);
    stream->buf = NULL;
    stream->curr = NULL;
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
            char prefix[PRINT_BUFFER_SIZE];
            prefix[0] = '\0';
            snprintf(prefix, PRINT_BUFFER_SIZE, "After opening %d file", (i + 1));
            print_file_table(prefix);
        }
    }
    
    for (int i = 0; i < NUM_FILES_WITHIN_LIMITS; ++i) {
        if (debug) {
            char prefix[PRINT_BUFFER_SIZE];
            prefix[0] = '\0';
            snprintf(prefix, PRINT_BUFFER_SIZE, "Before closing %d file", (i + 1));
            print_file_table(prefix);
        }
        
        if (check_fd_count(NUM_FILES_WITHIN_LIMITS - i) != 0) {
            return 1;
        }
        
        my_fclose(open_files[i]);
        
        if (debug) {
            char prefix[PRINT_BUFFER_SIZE];
            prefix[0] = '\0';
            snprintf(prefix, PRINT_BUFFER_SIZE, "After closing %d file", (i + 1));
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

int test_create(int debug) {
    const char *new_file_name = "tests/data/creat.txt";

    if (check_fd_count(0) != 0) {
        return 1;
    }
    
    MY_FILE *f = my_fopen(new_file_name, "w");
    if (f == NULL) {
        printf("ERROR: Unable to creat the file %s\n", new_file_name);
        return 1;
    }

    if (check_fd_count(1) != 0) {
        return 1;
    }

    printf("Created file fd = %d\n", f->fd);

    my_fclose(f);

    if (check_fd_count(0) != 0) {
        return 1;
    }
    
    return 0;
}

int test_append(int debug) {
    const char *file_name = "tests/data/append.txt";

    if (check_fd_count(0) != 0) {
        return 1;
    }
    
    MY_FILE *f = my_fopen(file_name, "a");
    if (f == NULL) {
        printf("ERROR: Unable to creat/open the file %s\n", file_name);
        return 1;
    }

    if (check_fd_count(1) != 0) {
        return 1;
    }

    printf("Append file fd = %d\n", f->fd);
    my_fclose(f);

    if (check_fd_count(0) != 0) {
        return 1;
    }
    
    return 0;
}

int test_fgetc(int debug) {
    const char *file_name = "tests/data/input.txt";

    MY_FILE *f = my_fopen(file_name, "r");
    if (f == NULL) {
        printf("ERROR: Unable to open the file for reading %s\n", file_name);
        return 1;
    }

    int c;
    while((c = my_fgetc(f)) != EOF) {
        printf("fgetc read c = %c\n", c);
    }

    printf("fgetc done\n");

    my_fclose(f);

    return 0;
}


int test_fputc(int debug) {
    const char *new_file_name = "tests/data/creat.txt";

    if (check_fd_count(0) != 0) {
        return 1;
    }
    
    MY_FILE *f = my_fopen(new_file_name, "w");
    if (f == NULL) {
        printf("ERROR: Unable to creat the file %s\n", new_file_name);
        return 1;
    }

    if (check_fd_count(1) != 0) {
        return 1;
    }

    printf("Created file fd = %d\n", f->fd);

    const char * data = "This is a small sentence that I am going to write. Now I will explicitly\n"
                        "add a newline. It is on a newline now. Let's add some more, what,\n"
                        "punctuation marks. We have come a long way!!!";

    
    for (int i = 0; data[i] != '\0'; ++i) {
        printf("Char = %c, sleeping for 1s\n", data[i]);
        // sleep(1);
        my_fputc(data[i], f);
    }
    // This is to ensure a flush of buffer
    // TODO: Find a better way?
    // 1. Maybe we should flush the buffer at the time of closing for write mode
    // 2. Read until '\0' and flush at '\0'
    my_fputc(EOF, f);
    
    my_fclose(f);

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

    if ((failed = test_create(0)) != 0)
    {
        printf("ERROR: test_create\n");
    }

    if ((failed = test_append(0)) != 0)
    {
        printf("ERROR: test_append\n");
    }

    if ((failed = test_fgetc(0)) != 0)
    {
        printf("ERROR: test_fgetc\n");
    }

    if ((failed = test_fputc(0)) != 0)
    {
        printf("ERROR: test_fputc\n");
    }

    if (failed) {
        printf("ERROR: Failed with some tests\n");
    }

    return 0;
}
