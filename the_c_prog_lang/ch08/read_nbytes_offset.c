// This define is needed for SEEK_DATA
#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
// #include <fcntl.h>
// #include <error.h>
#include <stdlib.h>
// #include <string.h>


void print_usage(int is_error, const char *argv_0) {
    fprintf((is_error) ? stderr : stdout,
            "Usage: %s [-h] [-v] [-f file] [-n nbytes] [-o offset]\n",
             argv_0);
    fprintf((is_error) ? stderr : stdout,
            "  -h  Help\n");
    fprintf((is_error) ? stderr : stdout,
            "  -v  Enable SEEK_DATA version (Default SEEK_SET)\n");
    fprintf((is_error) ? stderr : stdout,
            "  -f  File to seek\n");
    fprintf((is_error) ? stderr : stdout,
            "  -n  Maximum number of bytes to be read. Must be positive number\n");
    fprintf((is_error) ? stderr : stdout,
            "  -o  Offset from where to start reading. Must be non-negative\n");
    fprintf((is_error) ? stderr : stdout,
            "\nExample: %s -v -f some_file.txt -n 16 -o 10\n\n",
            argv_0);
}


int string_to_size_t(const char *input, size_t *num) {
    char *endptr = NULL;
    unsigned long long val = strtoull(input, &endptr, 10);

    if (*endptr != '\0') {
        fprintf(stderr, "Invalid input %s to convert to size_t\n", input);
        return -1;
    }

    *num = (size_t)val;

    return 0;
}


int string_to_long(const char *input, off_t *num) {
    char *endptr = NULL;
    long long val = strtoll(input, &endptr, 10);

    if (*endptr != '\0') {
        fprintf(stderr, "Invalid input %s to convert to long\n", input);
        return -1;
    }

    *num = (off_t)val;

    return 0;
}


int read_nbytes_from_pos_seek_set(int fd, off_t pos, size_t nbytes, char *buf) {
    return 0;
}


int read_nbytes_from_pos_seek_data(int fd, off_t pos, size_t nbytes, char *buf) {
    return 0;
}


int main(int argc, char *argv[]) {
    printf("Read nbytes given an offset from a file\n");
    int opt;

    int use_seek_data = 0;
    char * inp_file = NULL;
    size_t nbytes = 0;
    off_t offset = 0;
    while ((opt = getopt(argc, argv, "hvf:n:o:")) != -1) {
        printf("opt = %c\n", (char)opt);
        switch (opt) {
        case 'h':
            printf("Option h\n");
            print_usage(0, argv[0]);
            return 0;
        case 'v':
            printf("Option v\n");
            use_seek_data = 1;
            break;
        case 'f':
            printf("Option f with arg %s\n", optarg);
            inp_file = optarg;
            break;
        case 'n':
            printf("Option n with arg %s\n", optarg);
            if (string_to_size_t(optarg, &nbytes) == -1) {
                return 1;
            }
            break;
        case 'o':
            printf("Option o with arg %s\n", optarg);
            if (string_to_long(optarg, &offset) == -1) {
                return 1;
            }
            break;
        default:
            print_usage(1, argv[0]);
            return 1;
        }
    }

    printf("argc = %d, optind = %d\n", argc, optind);

    if (inp_file == NULL) {
        fprintf(stderr, "\nPlease provide an input file using \"-f some_file\" option\n\n");
        print_usage(1, argv[0]);
        return 1;
    }

    if (nbytes == 0) {
        fprintf(stderr, "\nnbytes has to be a positive number\n\n");
        print_usage(1, argv[0]);
        return 1;
    }

    if (offset >= 0) {
        fprintf(stderr, "\nOffset must be non-negative\n\n");
        print_usage(1, argv[0]);
        return 1;
    }

    printf("use_seek_data = %d, file = %s, nbytes = %zu, offset = %ld\n", use_seek_data, inp_file, nbytes, offset);

    int nread = 0;
    if (use_seek_data) {
        nread = read_nbytes_from_pos_seek_data(0, 0, 0, NULL);
    } else {
        nread = read_nbytes_from_pos_seek_set(0, 0, 0, NULL);
    }

    printf("nread = %d\n", nread);

    return 0;
}
