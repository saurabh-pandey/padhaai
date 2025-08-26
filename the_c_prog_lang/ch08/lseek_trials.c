// This define is needed for SEEK_DATA
#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <error.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_SIZE 100

// This function uses SEEK_SET to seek into a file
// SEEK_SET doesn't fail even when we seek beyond the EOF. It is only later that a call to read
// that returns 0 confirms EOF. Thus it is an approach where we seek and read until we detect EOF.
ssize_t seek_set_opened_file(int fd, off_t offset, char * buffer, int nbytes) {
    // printf("Seeking using SEEK_SET fd = %d at offset = %ld for bytes = %d\n", fd, offset, nbytes);
    off_t ret = lseek(fd, offset, SEEK_SET);

    // printf("  lseek ret = %ld\n", ret);

    if (ret == -1) {
        char error_msg[100];
        snprintf(error_msg, sizeof(error_msg), "Error while seeking fd %d", fd);
        perror(error_msg);
        return -1;
    }

    const ssize_t nread = read(fd, buffer, nbytes);
    // printf("  nread = %ld\n", nread);
    if (nread == -1) {
        char error_msg[100];
        snprintf(error_msg, sizeof(error_msg), "Error while reading fd %d", fd);
        perror(error_msg);
        return -1;
    }

    // printf("  Output:\n");
    // write(1, buffer, nread);
    // write(1, "\n", 2);
    return nread;
}


// This function uses SEEK_DATA to seek into a file
// SEEK_DATA fails i.e returns -1 when we seek beyond the EOF. Thus we don't need a read call to
// detect EOF.
ssize_t seek_data_opened_file(int fd, off_t offset, char * buffer, int nbytes) {
    // printf("Seeking using SEEK_DATA fd = %d at offset = %ld for bytes = %d\n", fd, offset, nbytes);
    off_t ret = lseek(fd, offset, SEEK_DATA);

    // printf("  lseek ret = %ld\n", ret);

    if (ret == -1) {
        // char error_msg[100];
        // snprintf(error_msg, sizeof(error_msg), "Error while seeking fd %d", fd);
        // perror(error_msg);
        return 0;
    }

    const ssize_t nread = read(fd, buffer, nbytes);
    // printf("  nread = %ld\n", nread);
    if (nread == -1) {
        char error_msg[100];
        snprintf(error_msg, sizeof(error_msg), "Error while reading fd %d", fd);
        perror(error_msg);
        return -1;
    }

    // printf("  Output:\n");
    // write(1, buffer, nread);
    // write(1, "\n", 1);
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

    printf("\n");
    printf("%-10s %-10s %-10s\n", "offset", "bytes", "nread");
    printf("=================================\n");

    int total_cycles = 0;
    ssize_t nread = 0;
    off_t offset = 0;
    const int jump = 5;
    do {
        nread = 0;
        int nbytes = 1;
        const int nbytes_jump = 5;
        int prev_nread = nread;
        do {
            total_cycles += 1;
            prev_nread = nread;
            // printf("\n");
            
            char buffer1[MAX_BUFFER_SIZE] = "";
            const ssize_t nread1 = seek_set_opened_file(fd, offset, buffer1, nbytes);
            
            char buffer2[MAX_BUFFER_SIZE] = "";
            const ssize_t nread2 = seek_data_opened_file(fd, offset, buffer2, nbytes);

            if (nread1 != nread2) {
                printf("ERROR: nread mismatch\n");
            } else {
                nread = nread1;
                printf("%-10ld %-10d %-10zd\n", offset, nbytes, nread);
            }

            if (strcmp(buffer1, buffer2) != 0) {
                printf("ERROR: Buffer mismatch\n");
            }
            
            // printf("\n");
            
            nbytes += nbytes_jump;
            // printf("  nread = %d, prev_nread = %d\n", nread, prev_nread);
        } while (nread > prev_nread); // Increase buffer until we don't read more than previous
        offset += jump;
    } while (nread > 0);

    printf("\n\nTotal cycles = %d\n\n", total_cycles);

    close(fd);

    return 0;
}
