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
    // Seek using SEEK_SET for seeking from file start
    const off_t ret = lseek(fd, offset, SEEK_SET);
    if (ret == -1) {
        char error_msg[MAX_BUFFER_SIZE];
        snprintf(error_msg, sizeof(error_msg), "Error while seeking fd %d", fd);
        perror(error_msg);
        return -1;
    }

    // Read now nbytes starting from offset into the buffer
    const ssize_t nread = read(fd, buffer, nbytes);
    if (nread == -1) {
        char error_msg[MAX_BUFFER_SIZE];
        snprintf(error_msg, sizeof(error_msg), "Error while reading fd %d", fd);
        perror(error_msg);
        return -1;
    }

    return nread;
}


// This function uses SEEK_DATA to seek into a file
// SEEK_DATA fails i.e returns -1 when we seek beyond the EOF. Thus we don't need a read call to
// detect EOF.
ssize_t seek_data_opened_file(int fd, off_t offset, char * buffer, int nbytes) {
    // Seek using SEEK_DATA and error if go beyond EOF
    const off_t ret = lseek(fd, offset, SEEK_DATA);
    if (ret == -1) {
        // EOF so return 0 bytes read
        return 0;
    }

    // Read now nbytes starting from offset into the buffer
    const ssize_t nread = read(fd, buffer, nbytes);
    if (nread == -1) {
        char error_msg[MAX_BUFFER_SIZE];
        snprintf(error_msg, sizeof(error_msg), "Error while reading fd %d", fd);
        perror(error_msg);
        return -1;
    }

    return nread;
}


// This program tries to open a file given as the argument and then read at many offsets for a 
// range of bytes. This array like reading of file is done using lseek command.
// It also uses two different ways to call lseek.
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s input_file\n", argv[0]);
        return -1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        char error_msg[MAX_BUFFER_SIZE];
        snprintf(error_msg, sizeof(error_msg), "Error while opening %s", argv[1]);
        perror(error_msg);
        exit(1);
    }

    printf("\n");
    printf("%-10s %-10s %-10s %-10s\n", "index", "offset", "bytes", "nread");
    printf("========================================\n");

    int total_cycles = 0;
    ssize_t nread = 0;
    off_t offset = 0;
    const int offset_jump = 5;
    do {
        nread = 0;
        int nbytes = 1;
        const int nbytes_jump = 5;
        while (1) {
            total_cycles += 1;
            
            char buffer1[MAX_BUFFER_SIZE] = "";
            const ssize_t nread1 = seek_set_opened_file(fd, offset, buffer1, nbytes);
            
            char buffer2[MAX_BUFFER_SIZE] = "";
            const ssize_t nread2 = seek_data_opened_file(fd, offset, buffer2, nbytes);

            if (nread1 != nread2) {
                printf("ERROR: nread mismatch\n");
            } else {
                nread = nread1;
                printf("%-10d %-10ld %-10d %-10zd\n", total_cycles, offset, nbytes, nread);
            }

            if (strcmp(buffer1, buffer2) != 0) {
                printf("ERROR: Buffer mismatch\n");
            }
            if (nread < nbytes) {
                // For this offset the buffer was bigger than the amount of data available. It is 
                // of no use to further increase the buffer size. This is time to take a break!
                break;
            }
            
            nbytes += nbytes_jump;
        }
        
        offset += offset_jump;
        
        printf("\n"); // New offset vertical separator in the table
    } while (nread > 0);

    // printf("\n\nTotal cycles = %d\n\n", total_cycles);

    close(fd);

    return 0;
}
