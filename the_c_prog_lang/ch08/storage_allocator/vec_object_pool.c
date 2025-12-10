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

PoolItem pool[MAX_POOL_SIZE];
const PoolItem init = {1, {-1, -1, -1}};

void initialize_pool(void) {
    for (int i = 0; i < sizeof(pool)/sizeof(PoolItem); ++i) {
        pool[i] = init;
    }
}

Vector * borrow(void) {
    for (int i = 0; i < sizeof(pool)/sizeof(PoolItem); ++i) {
        // printf("borrow i = %d, is_free = %d\n", i, pool[i].is_free);
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

void init_vec(Vector * v, int x, int y, int z) {
    if (v == NULL) {
        return;
    }
    v->x = x;
    v->y = y;
    v->z = z;
}

void single_action(void) {
    const int max_trials = 10;

    for (int i = 0; i < max_trials; ++i) {
        Vector * v = borrow();
        init_vec(v, i, i, i);
        
        print_vec(v);
        
        yield(v);
    }
}

void double_action(void) {
    const int max_trials = 10;

    for (int i = 0; i < max_trials; ++i) {
        Vector * v1 = borrow();
        init_vec(v1, i, i, i);
        print_vec(v1);

        Vector * v2 = borrow();
        init_vec(v2, i - max_trials, i - max_trials, i - max_trials);
        print_vec(v2);
        
        yield(v1);
        yield(v2);
    }
}

void multi_action(int num_borrows) {
    const int max_trials = 10;
    Vector * vecs[20] = {NULL};

    for (int i = 0; i < max_trials; ++i) {
        for (int j = 0; j < num_borrows; ++j) {
            vecs[j] = borrow();
            if (vecs[j] == NULL) {
                printf("Borrow no %d failed\n", j);
            }
            init_vec(vecs[j], i, i, i);
            print_vec(vecs[j]);
        }
        for (int j = 0; j < num_borrows; ++j) {
            yield(vecs[j]);
            vecs[j] = NULL;
        }
    }
}

void multi_action_inverse_yield(int num_borrows) {
    const int max_trials = 10;
    Vector * vecs[20] = {NULL};

    for (int i = 0; i < max_trials; ++i) {
        for (int j = 0; j < num_borrows; ++j) {
            vecs[j] = borrow();
            if (vecs[j] == NULL) {
                printf("Borrow no %d failed\n", j);
            }
            init_vec(vecs[j], i, i, i);
            print_vec(vecs[j]);
        }
        for (int j = num_borrows - 1; j > -1; --j) {
            yield(vecs[j]);
            vecs[j] = NULL;
        }
    }
}

void multi_action_worst(int num_borrows) {
    const int max_trials = 10;
    Vector * vecs[20] = {NULL};

    for (int i = 0; i < max_trials; ++i) {
        Vector * last_borrowed = NULL;
        for (int j = 0; j < num_borrows; ++j) {
            vecs[j] = borrow();
            if (vecs[j] == NULL) {
                printf("Borrow no %d failed\n", j);
            } else {
                last_borrowed = vecs[j];
            }
            init_vec(vecs[j], i, i, i);
            print_vec(vecs[j]);
        }
        // yield and borrow this last borrowed object
        printf("Testing worst case for %p\n", last_borrowed);
        for (int j = 0; j < 100000; ++j) {
            yield(last_borrowed);
            last_borrowed = borrow();
        }
        for (int j = num_borrows - 1; j > -1; --j) {
            yield(vecs[j]);
            vecs[j] = NULL;
        }
    }
}

int main(int argc, char * argv[]) {
    printf("Testing Vector memory pool\n");

    initialize_pool();

    // single_action();
    // double_action();

    multi_action(5);
    multi_action(11);

    multi_action_inverse_yield(5);

    multi_action_inverse_yield(12);

    multi_action_worst(12);

    return 0;
}
