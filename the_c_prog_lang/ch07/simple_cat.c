#include <stdio.h>
#include <unistd.h>
#include <linux/limits.h>


int main(int argc, char *argv[]) {
    printf("Running simple_cat\n");

    char cwd[PATH_MAX];
   if (getcwd(cwd, sizeof(cwd)) != NULL) {
       printf("Current working dir: %s\n", cwd);
   } else {
       perror("getcwd() error");
       return 1;
   }

   char exec_path[PATH_MAX];
   ssize_t len = readlink("/proc/self/exe", exec_path, sizeof(exec_path) - 1);
    if (len == -1) {
        perror("Error reading symbolic link");
        return 1;
    }

    // Null-terminate the path
    exec_path[len] = '\0';

    printf("Path to exec is '%s'\n", exec_path);


    FILE *fp;
    if ((fp = fopen("tests/data/text1.txt", "r")) != NULL) {
        int c = 0;
        while ((c = getc(fp)) != EOF) {
            putc(c, stdout);
        }
    } else {
        printf("ERROR: fp is null\n");
    }

    printf("Done\n");
    return 0;
}