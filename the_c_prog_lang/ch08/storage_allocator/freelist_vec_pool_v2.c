/* This file contains a fixed size object pool. It serves only a Vector object and can accept it 
back into the pool.
This simple fixed size vec object pool serves as a simpler example towards understand a generic
storage allocator.
It is based on the following youtube video by Jacob Sorber titled "Making allocators and object pools faster using a free list"
Link to the video is: https://www.youtube.com/watch?v=MxgnS9Lwv0k
*/

#include "freelist_vec_pool.h"

#include <stdio.h>


#define MAX_POOL_SIZE 10000
#define MAX_BORROWS MAX_POOL_SIZE + 100


Vector vector_pool[MAX_POOL_SIZE];
const Vector init = {-1, -1, -1};

typedef struct FreeList {
    size_t vec_id;
    struct FreeList * next;
} FreeList;

FreeList pool[MAX_POOL_SIZE];

FreeList * head = NULL;


void initialize_pool(void) {
    for (size_t i = 0; i < MAX_POOL_SIZE - 1; ++i) {
        vector_pool[i] = init;
        pool[i].vec_id = i;
        pool[i].next = &(pool[i]);
    }
    pool[MAX_POOL_SIZE - 1].vec_id = MAX_POOL_SIZE - 1;
    pool[MAX_POOL_SIZE - 1].next = NULL;
    
    head = pool;
}


Vector * borrow(void) {
    if (head == NULL) {
        return NULL;
    }
    Vector * v = &(vector_pool[head->vec_id]);

    FreeList * old_head = head;

    head = head->next;
    old_head->next = NULL;
    return v;
}


int yield(Vector * v) {
    if (v == NULL) {
        return -1;
    }
    
    size_t id = (v - vector_pool) / sizeof(vector_pool[0]);

    if (id > (MAX_POOL_SIZE - 1)) {
        printf("ERROR: Vector to be yielded is out-of-bounds\n");
        return -1;
    }
    
    FreeList * fl = &(pool[id]);
    // printf("New free list next = %p\n", fl->next);
    fl->next = head;
    head = fl;

    return id;
}

