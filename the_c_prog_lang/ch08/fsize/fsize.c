#include "fsize.h"

#include <stdio.h>

void fsize(char * name) {
    printf("Calling fsize with name = %s\n", name);

    // Check if name points to a file.
    // If it is a file print the size and return
    // Else it is a directory.
    // In the case of dir we list all files inside the dir and run fsize on each entry
    // Thus fsize calls itself recursively when the name point to a directory
}
