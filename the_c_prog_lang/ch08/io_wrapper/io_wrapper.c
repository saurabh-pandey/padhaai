#include "io_wrapper.h"

#include <stdio.h>

#include <fcntl.h> // open(), creat()
#include <unistd.h> // close(), lseek()

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


// File mode flags
#define FLAG_READ  0x01 // 0001
#define FLAG_WRITE 0x02 // 0010
#define FLAG_EOF   0x04 // 0100
#define FLAG_UNBUF 0x08 // 1000


// Actual definition is hidden inside the source thus making MY_FILE struct opaque
typedef struct MY_FILE {
    int fd; // File descriptor
    char *buf; // Buffer
    char *curr; // Read pointer to buffer
    size_t count; // Amount of buffer in use
    int flag; // Mode of file
} MY_FILE;

// File table of the process
MY_FILE file_table[MAX_FILES];


static void print_my_file(MY_FILE *f) {
    if (f == NULL) {
        printf("NULL");
    } else {
        printf("{fd = %d, ", f->fd);
        printf("buf = %s, ", f->buf == NULL ? "NULL" : f->buf);
        printf("curr = %s, ", f->curr == NULL ? "NULL" : f->curr);
        printf("count = %ld, ", f->count);
        printf("flag = %d}", f->flag);
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


static MY_FILE *fetch_first_free_file_from_table() {
    for (int i = 0; i < MAX_FILES; ++i) {
        MY_FILE *curr_f = &(file_table[i]);
        if (curr_f->fd == -1) {
            return curr_f;
        }
    }
    return NULL;
}

static MY_FILE *create_file_from_fd(int fd) {
    MY_FILE *f = fetch_first_free_file_from_table();
    if (f == NULL) {
        printf("ERROR: Seems like file table is full\n");
        return NULL;
    }
    f->fd = fd;
    f->buf = NULL;
    f->curr = NULL;
    f->count = 0;
    f->flag = 0;
    return f;
}


int count_open_fds() {
    int total_used_fds = 0;
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
            MY_FILE *f = create_file_from_fd(fd);
            f->flag |= FLAG_READ;
            return f;
            break;
        }
        case 'w':
        {
            // Write mode
            const int fd = creat(pathname, FILE_CREATE_PERMS);
            if (fd == -1) {
                return NULL;
            }
            MY_FILE *f = create_file_from_fd(fd);
            f->flag |= FLAG_WRITE;
            return f;
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
            
            // Move to the end of file for appending
            const off_t ret = lseek(fd, 0, SEEK_END);
            if (ret == -1) {
                printf("Error while moving to the end\n");
                return NULL;
            }
            MY_FILE *f = create_file_from_fd(fd);
            f->flag |= FLAG_WRITE;
            return f;
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
    if (stream == NULL) {
        printf("Error: NULL stream in my_fgetc\n");
        return -1;
    }

    if ((stream->flag & FLAG_READ) == 0) {
        printf("Error: File not in read mode for fd %d\n", stream->fd);
    }

    if (stream->count == 0) {
        const int bufsize = (stream->flag & FLAG_UNBUF) ? 1 : READ_BUFFER_SIZE;
        if (stream->buf == NULL) {
            if ((stream->buf = (char *)malloc(bufsize)) == NULL) {
                printf("Error: Failed to allocate buffer while reading for fd %d\n", stream->fd);
                return EOF;
            }
        }
        int nread = 0;
        if ((nread = read(stream->fd, stream->buf, bufsize)) < 0) {
            printf("Error: Failed to read from file fd %d\n", stream->fd);
            return EOF;
        }
        stream->count = nread;
        stream->curr = stream->buf;
    }

    if (stream->count == 0) {
        return EOF;
    }

    int c = *(stream->curr);
    (stream->curr)++;
    (stream->count)--;
    
    return c;
}


int my_fflush(MY_FILE *stream) {
    if (stream == NULL) {
        // TODO: Here libc flushes all write streams in the file table
        return 0;
    }

    if ((stream->flag & FLAG_WRITE) == 0) {
        // Not a write stream so don't do anything for now
        return 0;
    }

    ssize_t nwrite = 0;
    if ((nwrite = write(stream->fd, stream->buf, stream->count)) < 0) {
        printf("Error: Failed to write from file fd %d\n", stream->fd);
        return EOF;
    }

    stream->count = 0;
    stream->curr = stream->buf;
    return 0;
}


int my_fputc(int c, MY_FILE *stream) {
    if (stream == NULL) {
        printf("Error: NULL stream in my_fputc\n");
        return -1;
    }

    if ((stream->flag & FLAG_WRITE) == 0) {
        printf("Error: File not in write mode for fd %d\n", stream->fd);
    }

    const int bufsize = (stream->flag & FLAG_UNBUF) ? 1 : WRITE_BUFFER_SIZE;
    if (stream->buf == NULL) {
        if ((stream->buf = (char *)malloc(bufsize)) == NULL) {
            printf("Error: Failed to allocate buffer while writing for fd %d\n", stream->fd);
            return EOF;
        }
        stream->curr = stream->buf;
    }

    if (c != EOF) {
        *(stream->curr) = (char)c;
        (stream->curr)++;
        (stream->count)++;
    }

    if ((stream->count == bufsize) || (c == '\n') || (c == EOF)) {
        my_fflush(stream);
    }
    
    return c;
}


int my_fseek(MY_FILE *stream, long offset, int whence) {
    // Update the stream and then do the below syscall. Finally check for errors.

    if (stream == NULL) {
        return -1;
    }

    // Flush all buffered data for writing
    my_fflush(stream);

    off_t res = 0;
    if ((res = lseek(stream->fd, offset, whence)) < 0) {
        return -1;
    }

    // Reset the buffer in case of read
    stream->curr = stream->buf;
    stream->count = 0;

    return res;
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

    if (stream->flag & FLAG_WRITE) {
        my_fflush(stream);
    }

    // Reset and Free this table entry
    const int fd = stream->fd;
    stream->fd = -1;
    free(stream->buf);
    stream->buf = NULL;
    stream->curr = NULL;
    stream->count = 0;
    stream->flag = 0;

    return close(fd);
}

__attribute__((constructor))
static void my_init(void) {
    // Initialize the file table
    FILL_ARRAY(file_table, ((MY_FILE){-1, "", NULL, 0, 0}));

    // Initialize std in, out and err fds
    my_stdin = create_file_from_fd(0);
    my_stdin->flag |= FLAG_READ;

    my_stdout = create_file_from_fd(1);
    my_stdout->flag |= FLAG_WRITE;

    my_stderr = create_file_from_fd(2);
    my_stderr->flag |= FLAG_WRITE;
}
