#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <error.h>
#include <stdlib.h>


// int get_n_bytes(int fd, off_t pos, char *buf, int n) {
//     return 0;
// }


int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s input_file\n", argv[0]);
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        char error_msg[100];
        snprintf(error_msg, sizeof(error_msg), "Error while opening file %s", argv[1]);
        perror(error_msg);
        exit(1);
    }

    // off_t ret = lseek(fd, 45, SEEK_CUR);
    off_t ret = lseek(fd, 50, SEEK_DATA);

    printf("ret = %ld\n", ret);

    if (ret == -1) {
        char error_msg[100];
        snprintf(error_msg, sizeof(error_msg), "Error while lseeking file %s", argv[1]);
        perror(error_msg);
        exit(1);
    }

    char buffer[100];
    ssize_t nread = read(fd, buffer, 10);
    if (nread == -1) {
        char error_msg[100];
        snprintf(error_msg, sizeof(error_msg), "Error while reading file %s", argv[1]);
        perror(error_msg);
        exit(1);
    }

    write(1, buffer, nread);

    return 0;
}