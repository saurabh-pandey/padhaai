#ifndef TCPL_CH08_STORAGE_ALLOCATOR_LINEAR_VEC_POOL_H
#define TCPL_CH08_STORAGE_ALLOCATOR_LINEAR_VEC_POOL_H

#include "just_vec.h"

#define MAX_POOL_SIZE 10000
#define MAX_BORROWS MAX_POOL_SIZE + 100

// Call this before any borrow or yield
void initialize_pool(void);

Vector * borrow(void);

int yield(Vector * v);

#endif // #ifndef TCPL_CH08_STORAGE_ALLOCATOR_LINEAR_VEC_POOL_H