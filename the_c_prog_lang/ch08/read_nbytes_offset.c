// This define is needed for SEEK_DATA
#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
// #include <fcntl.h>
// #include <error.h>
// #include <stdlib.h>
// #include <string.h>


int read_nbytes_from_pos_seek_set(int fd, off_t pos, size_t nbytes, char *buf) {
    return 0;
}


int read_nbytes_from_pos_seek_data(int fd, off_t pos, size_t nbytes, char *buf) {
    return 0;
}


int main(int argc, char *argv[]) {
    printf("Read nbytes given an offset from a file\n");
    int opt;
    while ((opt = getopt(argc, argv, "ab:c:")) != -1) {
        switch (opt) {
        case 'a':
            printf("Option a\n");
            break;
        case 'b':
            printf("Option b with arg %s\n", optarg);
            break;
        case 'c':
            printf("Option c with arg %s\n", optarg);
            break;
        default:
            fprintf(stderr, "Usage: %s [-a] [-b val] [-c val]\n", argv[0]);
            return 1;
        }
    }

    return 0;
}
