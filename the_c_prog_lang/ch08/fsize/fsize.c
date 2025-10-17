#include "fsize.h"

#include <stdio.h>
#include <sys/stat.h>

void fsize(const char * name) {
    printf("Calling fsize with name = %s\n", name);

    struct stat st;
    if (stat(name, &st) == -1) {
        perror("Error in stat");
        return;
    }
    
    if (S_ISREG(st.st_mode)) {
        printf("%s is a regular file\n", name);
        printf("%s size = %ld\n", name, st.st_size);
    } else if (S_ISDIR(st.st_mode)) {
        printf("%s is a directory\n", name);
    } else {
        printf("%s is something else (socket, symlink, device, etc.).\n", name);
    }
}
