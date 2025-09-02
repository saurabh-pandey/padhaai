// This define is needed for SEEK_DATA
#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>


#define MAX_CHAR_ARR_SIZE 100
#define MAX_BUFFER_SIZE 1000


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
    if (lseek(fd, pos, SEEK_SET) == -1) {
        return -1;
    }
    return read(fd, buf, nbytes);
}


int read_nbytes_from_pos_seek_data(int fd, off_t pos, size_t nbytes, char *buf) {
    if (lseek(fd, pos, SEEK_DATA) == -1) {
        return -1;
    }
    return read(fd, buf, nbytes);
}


typedef struct _arg_val {
    int use_seek_data;
    char * inp_file;
    size_t nbytes;
    off_t offset;
} ArgVal;


int parse_args(int argc, char *argv[], ArgVal *vals) {
    int opt;

    while ((opt = getopt(argc, argv, "hvf:n:o:")) != -1) {
        switch (opt) {
        case 'h':
            print_usage(0, argv[0]);
            return 0;
        case 'v':
            vals->use_seek_data = 1;
            break;
        case 'f':
            vals->inp_file = optarg;
            break;
        case 'n':
            if (string_to_size_t(optarg, &(vals->nbytes)) == -1) {
                return -1;
            }
            break;
        case 'o':
            if (string_to_long(optarg, &(vals->offset)) == -1) {
                return -1;
            }
            break;
        default:
            fprintf(stderr, "\nERROR: Unknow option\n\n");
            print_usage(1, argv[0]);
            return -1;
        }
    }

    return 0;
}


int test_args_validity(ArgVal arg_val, char *exe) {
    if (arg_val.inp_file == NULL) {
        fprintf(stderr, "\nERROR: Please provide an input file using \"-f some_file\" option\n\n");
        print_usage(1, exe);
        return -1;
    }

    if (arg_val.nbytes == SIZE_MAX) {
        fprintf(stderr, "\nERROR: nbytes is a compulsory parameter\n\n");
        print_usage(1, exe);
        return -1;
    }

    if (arg_val.nbytes == 0) {
        fprintf(stderr, "\nERROR: nbytes has to be a positive number\n\n");
        print_usage(1, exe);
        return -1;
    }

    if (arg_val.offset < 0) {
        fprintf(stderr, "\nERROR: Offset must be non-negative\n\n");
        print_usage(1, exe);
        return -1;
    }

    return 0;
}


int main(int argc, char *argv[]) {
    ArgVal arg_val = {0, NULL, SIZE_MAX, -1};

    if (parse_args(argc, argv, &arg_val) == -1) {
        return 1;
    }

    if (test_args_validity(arg_val, argv[0]) == -1) {
        return 1;
    }
    
    const int fd = open(arg_val.inp_file, O_RDONLY);
    if (fd == -1) {
        char msg_prefix[MAX_CHAR_ARR_SIZE];
        snprintf(msg_prefix, sizeof(msg_prefix), "ERROR while opening file%s", arg_val.inp_file);
        perror(msg_prefix);
        exit(1);
    }

    int nread = 0;
    char buffer[MAX_BUFFER_SIZE];
    buffer[0] = '\0';
    if (arg_val.use_seek_data) {
        nread = read_nbytes_from_pos_seek_data(fd, arg_val.offset, arg_val.nbytes, buffer);
    } else {
        nread = read_nbytes_from_pos_seek_set(fd, arg_val.offset, arg_val.nbytes, buffer);
    }
    if (nread == -1) {
        char msg_prefix[MAX_CHAR_ARR_SIZE];
        snprintf(msg_prefix, sizeof(msg_prefix), "ERROR while read file %s", arg_val.inp_file);
        perror(msg_prefix);
        close(fd);
        exit(1);
    }
    buffer[nread] = '\0';

    printf("%s", buffer);

    close(fd);

    return 0;
}
