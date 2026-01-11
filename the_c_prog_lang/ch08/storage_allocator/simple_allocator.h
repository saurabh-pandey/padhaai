#ifndef TCPL_CH08_STORAGE_ALLOCATOR_SIMPLE_ALLOCATOR_H
#define TCPL_CH08_STORAGE_ALLOCATOR_SIMPLE_ALLOCATOR_H

#include <stddef.h>

// Storage Allocation Main API
void * my_malloc(size_t nbytes);

void my_free(void * p);


// Functions that provide info of the allocator
void print_mem_blocks(void);

void reset_cases(void);
void print_cases(void);

#endif