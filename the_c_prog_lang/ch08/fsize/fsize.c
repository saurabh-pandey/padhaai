#include "fsize.h"

#include <stdio.h>
#include <sys/stat.h>

void fsize(const char * name) {
    printf("Calling fsize with name = %s\n", name);

    // Check if name points to a file.
    // If it is a file print the size and return
    // Else it is a directory.
    // In the case of dir we list all files inside the dir and run fsize on each entry
    // Thus fsize calls itself recursively when the name point to a directory

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
