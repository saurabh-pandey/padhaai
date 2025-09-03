#include <stdio.h>

#include <fcntl.h> // open(), creat()
#include <unistd.h> // close()


#define MAX_FILES 100
#define MAX_CHAR_ARR_SIZE 100


typedef struct MY_FILE {
    int fd; // File descriptor
    char *buf; // Buffer
    char *curr; // Read pointer to buffer
    size_t count; // Amount of buffer still unread
} MY_FILE;

MY_FILE file_table[MAX_FILES];
size_t ft_index = 0;

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
            file_table[ft_index].fd = fd;
            return &file_table[ft_index];
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

int my_fclose(MY_FILE *stream) {
    // TODO: Might do some cleanup of other members of the file ptr
    printf("Closing file with fd = %d\n", stream->fd);
    return close(stream->fd);
}


int main(int argc, char *argv[]) {
    printf("Trying file ptr\n");

    MY_FILE *f = my_fopen(argv[1], "r");
    printf("Opened file fd = %d\n", f->fd);

    my_fclose(f);

    return 0;
}
