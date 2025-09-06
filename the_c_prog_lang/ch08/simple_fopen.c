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


MY_FILE *my_fopen(const char *pathname, const char *mode) {
    printf("Calling my_fopen for path = %s, mode = %s\n", pathname, mode);

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
    
    printf("Closing file with fd = %d\n", fd);
    return close(fd);
}


// Some ideas on how to drive this:
// 1. We have to call my_fopen, my_fclose, my_fgetc, my_fputc, my_fseek
// 2. my_fopen acquires a row in the file_table
// 3. my_fclose releases the passed row from the file_table
// 4. I Need to map the acquired resources to the ones that I want to close
// 5. I might pass my_fopen with a slot in the acquired table
// 6. Later I might use the above slot to close it
// 7. Slot allotted in step 5 might also be used in other in functions
// 8. State of file_table and function's response is tested
// An example test script (or playbook or tape) might look like:
// fopen, path0, mode0, 0
// file_table, 1
// fopen, path1, mode1, 1
// file_table, 2
// fclose, 1
// file_table, 1
// fopen, path2, mode2, 1
// file_table, 2
// fgetc, 0
// fputc, 1
// fclose, 1
// file_table, 1
// fclose, 0
// file_table, 0

int main(int argc, char *argv[]) {
    printf("Trying file ptr\n");

    FILL_ARRAY(file_table, ((MY_FILE){-1, "", NULL, 0}));

    print_file_table("Beginning");
    MY_FILE *open_files[6] = {NULL};
    for (int i = 0; i < 6; ++i) {
        MY_FILE *f = my_fopen(argv[1], "r");
        if (f == NULL) {
            printf("Unable to open the file %s\n", argv[1]);
            // return 1;
        } else {
            printf("Opened file fd = %d\n", f->fd);
            open_files[i] = f;
        }
        char prefix[BUFFER_SIZE];
        prefix[0] = '\0';
        snprintf(prefix, BUFFER_SIZE, "After opening %d file", (i + 1));
        print_file_table(prefix);
    }
    
    for (int i = 0; i < 6; ++i) {
        char prefix[BUFFER_SIZE];
        prefix[0] = '\0';
        snprintf(prefix, BUFFER_SIZE, "Before closing %d file", (i + 1));
        print_file_table(prefix);
        my_fclose(open_files[i]);
        prefix[0] = '\0';
        snprintf(prefix, BUFFER_SIZE, "After closing %d file", (i + 1));
        print_file_table(prefix);
    }

    print_file_table("End");

    return 0;
}
