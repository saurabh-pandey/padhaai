#ifndef TCPL_CH08_STORAGE_ALLOCATOR_SIMPLE_ALLOCATOR_H
#define TCPL_CH08_STORAGE_ALLOCATOR_SIMPLE_ALLOCATOR_H

#include <stddef.h>

// Storage Allocation Main API
void * my_malloc(size_t nbytes);

void my_free(void * p);

// For testing
void set_nalloc(size_t new_size);
size_t get_nalloc(void);


// Functions that provide info of the allocator
void print_mem_blocks(void);

void reset_cases(void);
void print_cases(void);

void print_stats(void);

#endif