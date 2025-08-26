#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <error.h>
#include <stdlib.h>

// This function uses SEEK_SET to seek into a file
// SEEK_SET doesn't fail even when we seek beyond the EOF. It is only later that a call to read
// that returns 0 confirms EOF. Thus it is an approach where we seek and read until we detect EOF.
ssize_t seek_set_opened_file(int fd, off_t offset, int nbytes) {
    printf("Seeking using SEEK_SET fd = %d at offset = %ld for bytes = %d\n", fd, offset, nbytes);
    off_t ret = lseek(fd, offset, SEEK_SET);

    printf("  lseek ret = %ld\n", ret);

    if (ret == -1) {
        char error_msg[100];
        snprintf(error_msg, sizeof(error_msg), "Error while seeking fd %d", fd);
        perror(error_msg);
        return -1;
    }

    char buffer[100];
    const ssize_t nread = read(fd, buffer, sizeof(buffer));
    printf("  nread = %ld\n", nread);
    if (nread == -1) {
        char error_msg[100];
        snprintf(error_msg, sizeof(error_msg), "Error while reading fd %d", fd);
        perror(error_msg);
        return -1;
    }

    printf("  Output:\n");
    write(1, buffer, nread);
    write(1, "\n", 2);
    return nread;
}


// This function uses SEEK_DATA to seek into a file
// SEEK_DATA fails i.e returns -1 when we seek beyond the EOF. Thus we don't need a read call to
// detect EOF.
ssize_t seek_data_opened_file(int fd, off_t offset, int nbytes) {
    printf("Seeking using SEEK_DATA fd = %d at offset = %ld for bytes = %d\n", fd, offset, nbytes);
    off_t ret = lseek(fd, offset, SEEK_DATA);

    printf("  lseek ret = %ld\n", ret);

    if (ret == -1) {
        char error_msg[100];
        snprintf(error_msg, sizeof(error_msg), "Error while seeking fd %d", fd);
        perror(error_msg);
        return -1;
    }

    char buffer[100];
    const ssize_t nread = read(fd, buffer, sizeof(buffer));
    printf("  nread = %ld\n", nread);
    if (nread == -1) {
        char error_msg[100];
        snprintf(error_msg, sizeof(error_msg), "Error while reading fd %d", fd);
        perror(error_msg);
        return -1;
    }

    printf("  Output:\n");
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

    int nread = 0;
    int offset = 0;
    const int jump = 5;
    do {
        printf("\n");
        nread = seek_set_opened_file(fd, offset, 10);
        nread = seek_data_opened_file(fd, offset, 10);
        printf("\n");
        offset += jump;
    } while (nread > 0);

    close(fd);

    return 0;
}