#ifndef TCPL_CH08_STORAGE_ALLOCATOR_SIMPLE_ALLOCATOR_H
#define TCPL_CH08_STORAGE_ALLOCATOR_SIMPLE_ALLOCATOR_H

#include <stddef.h>

void * my_malloc(size_t nbytes);

void my_free(void * p);

#endif