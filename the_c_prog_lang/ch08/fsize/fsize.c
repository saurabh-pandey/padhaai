#include "fsize.h"

#include <stdio.h>
#include <sys/stat.h>

#include <dirent.h>


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
        DIR *dir = opendir(name);
        if (!dir) {
            perror("opendir");
            return;
        }

        printf("Listing contents of dir: %s\n", name);
        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) {
            printf("  %s\n", entry->d_name);
        }

        closedir(dir);
    } else {
        printf("%s is something else (socket, symlink, device, etc.).\n", name);
    }
}
