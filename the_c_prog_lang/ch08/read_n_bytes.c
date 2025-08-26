#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <error.h>
#include <stdlib.h>


// int get_n_bytes(int fd, off_t pos, char *buf, int n) {
//     return 0;
// }

ssize_t seek_opened_file(int fd, off_t offset, int nbytes) {
    printf("Seeking fd = %d at offset = %ld for bytes = %d\n", fd, offset, nbytes);
    // off_t ret = lseek(fd, 45, SEEK_CUR);
    off_t ret = lseek(fd, offset, SEEK_DATA);

    printf("ret = %ld\n", ret);

    if (ret == -1) {
        char error_msg[100];
        snprintf(error_msg, sizeof(error_msg), "Error while seeking fd %d", fd);
        perror(error_msg);
        exit(1);
    }

    char buffer[100];
    const ssize_t nread = read(fd, buffer, nbytes);
    printf("nread = %ld\n", nread);
    if (nread == -1) {
        char error_msg[100];
        snprintf(error_msg, sizeof(error_msg), "Error while reading fd %d", fd);
        perror(error_msg);
        exit(1);
    }

    write(1, buffer, nread);
    write(1, "\n", 1);
    return nread;
}



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

    seek_opened_file(fd, 0, 10);
    seek_opened_file(fd, 5, 10);
    seek_opened_file(fd, 15, 10);
    seek_opened_file(fd, 20, 10);
    seek_opened_file(fd, 32, 10);
    seek_opened_file(fd, 34, 10);
    seek_opened_file(fd, 35, 10);
    seek_opened_file(fd, 36, 10);
    seek_opened_file(fd, 37, 10);

    close(fd);

    return 0;
}