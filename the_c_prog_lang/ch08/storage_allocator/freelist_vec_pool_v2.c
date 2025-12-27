/* This file contains a fixed size object pool. It serves only a Vector object and can accept it 
back into the pool.
This simple fixed size vec object pool serves as a simpler example towards understand a generic
storage allocator.
It is based on the following youtube video by Jacob Sorber titled "Making allocators and object pools faster using a free list"
Link to the video is: https://www.youtube.com/watch?v=MxgnS9Lwv0k
*/

#include "freelist_vec_pool.h"

#include <stdio.h>
#include <stddef.h>


#define MAX_POOL_SIZE 10000
#define MAX_BORROWS MAX_POOL_SIZE + 100


typedef struct FreeList {
    Vector vec;
    struct FreeList * next;
} FreeList;

FreeList pool[MAX_POOL_SIZE];

FreeList * head = NULL;


const Vector init = {-1, -1, -1};

void initialize_pool(void) {
    for (size_t i = 0; i < MAX_POOL_SIZE - 1; ++i) {
        pool[i].vec = init;
        pool[i].next = &(pool[i]);
    }
    pool[MAX_POOL_SIZE - 1].vec = init;
    pool[MAX_POOL_SIZE - 1].next = NULL;
    
    head = pool;
}


Vector * borrow(void) {
    if (head == NULL) {
        return NULL;
    }
    Vector * v = &(head->vec);

    FreeList * old_head = head;

    head = head->next;
    old_head->next = NULL;
    return v;
}


int yield(Vector * v) {
    if (v == NULL) {
        return -1;
    }
    
    FreeList * object_to_add = (FreeList *)((char *)v - offsetof(FreeList, vec));

    // Check if the vec is same as computed
    if (&(object_to_add->vec) != v) {
        printf("ERROR: Vector to be yielded is not correct\n");
        return -1;
    }
    
    object_to_add->next = head;
    head = object_to_add;

    return 1;
}

