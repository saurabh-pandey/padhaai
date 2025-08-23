#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>


void filecopy(int inp_fd, int out_fd) {
    char buffer[100];
    ssize_t n = 0;
    while ((n = read(inp_fd, buffer, sizeof buffer)) > 0) {
        if (write(out_fd, buffer, n) != n) {
            perror("Error while writing");
            exit(1);
        }
    }
}


int main(int argc, char * argv[]) {
    if (argc == 1) {
        filecopy(0, 1);
    } else {
        for (int i = 1; i < argc; ++i) {
            int in_fd = -1;
            if ((in_fd = open(argv[i], O_RDONLY)) == -1) {
                char fmt[100];
                snprintf(fmt, sizeof(fmt), "Error while opening %s", argv[i]);
                perror(fmt);
                exit(1);
            }
            filecopy(in_fd, 1);
        }
    }
    return 0;
}