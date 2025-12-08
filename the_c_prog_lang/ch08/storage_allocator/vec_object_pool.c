/* This file contains a fixed size object pool. It serves only a Vector object and can accept it 
back into the pool.
This simple fixed size vec object pool serves as a simpler example towards understand a generic
storage allocator.
It is based on the following youtube video by Jacob Sorber titled "What is an object pool, and how 
to create one in C?"
Link to the video is: https://www.youtube.com/watch?v=CpgsQLSc7KY
*/

#include <stdio.h>

typedef struct
{
    int x;
    int y;
    int z;
} Vector;

#define MAX_POOL_SIZE 10

typedef struct {
    int is_free;
    Vector v;
} PoolItem;

PoolItem pool[MAX_POOL_SIZE] = {{1, {-1, -1, -1}}};

Vector * borrow(void) {
    for (int i = 0; i < sizeof(pool)/sizeof(PoolItem); ++i) {
        if (pool[i].is_free == 1) {
            pool[i].is_free = 0;
            return &(pool[i].v);
        }
    }
    return NULL;
}

int yield(Vector * v) {
    if (v == NULL) {
        return -1;
    }
    
    for (int i = 0; i < sizeof(pool)/sizeof(PoolItem); ++i) {
        if (v == &(pool[i].v)) {
            if (pool[i].is_free != 0) {
                printf("ERROR: Returned object is already marked free\n");
                return -1;
            }
            pool[i].is_free = 1;
            return i;
        }
    }
    
    return -1;
}

void print_vec(const Vector * v) {
    if (v == NULL) {
        printf("{NULL}\n");
    } else {
        printf("{%d, %d, %d}\n", v->x, v->y, v->z);
    }
}

int main(int argc, char * argv[]) {
    printf("Testing Vector memory pool\n");

    const int max_trials = 10;

    for (int i = 0; i < max_trials; ++i) {
        Vector * v = borrow();
        if (v != NULL) {
            v->x = i;
            v->y = i;
            v->z = i;
        }

        print_vec(v);
        
        yield(v);
    }

    return 0;
}
