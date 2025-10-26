#include "fsize.h"

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#include <dirent.h>


void fsize(const char * name, int depth) {
    struct stat st;
    if (stat(name, &st) == -1) {
        perror("Error in stat");
        return;
    }
    
    if (S_ISREG(st.st_mode)) {
        for (int i = 0; i < depth; ++i) {
            printf(" ");
        }
        printf("%s size = %ld\n", name, st.st_size);
    } else if (S_ISDIR(st.st_mode)) {
        DIR *dir = opendir(name);
        if (!dir) {
            perror("opendir");
            return;
        }

        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) {
            char dir_path[PATH_MAX];

            sprintf(dir_path, "%s/%s", name, entry->d_name);
            // Don't recurse for . and .. folders as this would lead to infinite recursion
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
