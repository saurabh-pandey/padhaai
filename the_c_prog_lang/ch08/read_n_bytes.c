#include <stdio.h>
#include <unistd.h>


int get_n_bytes(int fd, off_t pos, char *buf, int n) {
    return 0;
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s input_file\n", argv[0]);
    }

    return 0;
}