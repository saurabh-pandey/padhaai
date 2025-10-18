#include "fsize.h"

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#include <dirent.h>

// #define MAX_PATH 100


void fsize(const char * name, int depth) {
    // printf("Calling fsize with name = %s\n", name);

    struct stat st;
    if (stat(name, &st) == -1) {
        perror("Error in stat");
        return;
    }
    
    if (S_ISREG(st.st_mode)) {
        // printf("%s is a regular file\n", name);
        for (int i = 0; i < depth; ++i) {
            printf(" ");
        }
        printf("%s size = %ld\n", name, st.st_size);
    } else if (S_ISDIR(st.st_mode)) {
        // printf("%s is a directory\n", name);
        DIR *dir = opendir(name);
        if (!dir) {
            perror("opendir");
            return;
        }

        // printf("Listing contents of dir: %s\n", name);
        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) {
            // printf("  %s\n", entry->d_name);
            char dir_path[PATH_MAX];

            sprintf(dir_path, "%s/%s", name, entry->d_name);

            // printf("  Path: %s\n", dir_path);
            if ((strcmp(entry->d_name, ".") != 0) && (strcmp(entry->d_name, "..") != 0))
            {
                fsize(dir_path, depth + 2);
            }
        }

        closedir(dir);
    } else {
        printf("%s is something else (socket, symlink, device, etc.).\n", name);
    }
}
