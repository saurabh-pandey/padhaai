#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#define PERMS 0666


int main(int argc, char * argv[]) {
    if (argc != 3) {
        printf("Usage: %s source_file copied_file\n", argv[0]);
        return 0;
    }

    int fd1 = -1;
    int fd2 = -1;
    if ((fd1 = open(argv[1], O_RDONLY)) == -1) {
        char fmt[100];
        snprintf(fmt, sizeof(fmt), "Error while opening %s", argv[1]);
        perror(fmt);
        exit(1);
    }
    if ((fd2 = creat(argv[2], PERMS)) == -1) {
        char fmt[100];
        snprintf(fmt, sizeof(fmt), "Error while creating %s", argv[2]);
        perror(fmt);
        exit(1);
    }
    char buffer[100];
    ssize_t n = 0;
    while ((n = read(fd1, buffer, sizeof buffer)) > 0) {
        if (write(fd2, buffer, n) != n) {
            perror("Error while writing");
            exit(1);
        }
    }
    
    return 0;
}
