/* This file contains a fixed size object pool. It serves only a Vector object and can accept it 
back into the pool.
This simple fixed size vec object pool serves as a simpler example towards understand a generic
storage allocator.
It is based on the following youtube video by Jacob Sorber titled "What is an object pool, and how 
to create one in C?"
Link to the video is: https://www.youtube.com/watch?v=CpgsQLSc7KY
*/

#include <stdio.h>
#include <time.h>

typedef struct {
    int x;
    int y;
    int z;
} Vector;

#define MAX_POOL_SIZE 10000
#define MAX_BORROWS MAX_POOL_SIZE + 100

typedef struct {
    int is_free;
    Vector v;
} PoolItem;

PoolItem pool[MAX_POOL_SIZE];
const PoolItem init = {1, {-1, -1, -1}};

void initialize_pool(void) {
    for (int i = 0; i < sizeof(pool)/sizeof(pool[0]); ++i) {
        pool[i] = init;
    }
}

Vector * borrow(void) {
    for (int i = 0; i < sizeof(pool)/sizeof(pool[0]); ++i) {
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
    
    for (int i = 0; i < sizeof(pool)/sizeof(pool[0]); ++i) {
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

void sequential_borrow_yield(int max_trials) {
    for (int i = 0; i < max_trials; ++i) {
        Vector * v = borrow();
        init_vec(v, i, i, i);
        yield(v);
    }
}


void yield_sequential_after_borrow(int max_trials) {
    Vector * vecs[MAX_BORROWS] = {NULL};
    for (int i = 0; i < max_trials; ++i) {
        for (int j = 0; j < MAX_BORROWS; ++j) {
            vecs[j] = borrow();
            init_vec(vecs[j], i, i, i);
        }
        for (int j = 0; j < MAX_BORROWS; ++j) {
            yield(vecs[j]);
            vecs[j] = NULL;
        }
    }
}

void yield_reverse_after_borrow(int max_trials) {
    Vector * vecs[MAX_BORROWS] = {NULL};
    for (int i = 0; i < max_trials; ++i) {
        for (int j = 0; j < MAX_BORROWS; ++j) {
            vecs[j] = borrow();
            init_vec(vecs[j], i, i, i);
        }
        // yielding in reverse
        for (int j = MAX_BORROWS - 1; j > -1; --j) {
            yield(vecs[j]);
            vecs[j] = NULL;
        }
    }
}

void yield_last_borrowed(int max_trials) {
    Vector * vecs[MAX_BORROWS] = {NULL};
    for (int i = 0; i < max_trials; ++i) {
        for (int j = 0; j < MAX_BORROWS; ++j) {
            vecs[j] = borrow();
            init_vec(vecs[j], i, i, i);
        }

        Vector * last_borrowed = vecs[MAX_POOL_SIZE - 1];
        // yield and borrow this last borrowed object for worst case
        // printf("Testing worst case for %p\n", last_borrowed);
        int max_yield = 0;
        for (int j = 0; j < MAX_POOL_SIZE; ++j) {
            int num_yield = yield(last_borrowed);
            max_yield = num_yield > max_yield ? num_yield : max_yield;
            last_borrowed = borrow();
        }
        // printf("Max yield ret val = %d, max pool %d\n", max_yield, MAX_POOL_SIZE);
        for (int j = MAX_BORROWS - 1; j > -1; --j) {
            yield(vecs[j]);
            vecs[j] = NULL;
        }
    }
}


#define TIME_FUNC_RET(seconds_var, func_call) do {                                  \
    struct timespec m_time_func_ret_t1, m_time_func_ret_t2;                         \
    clock_gettime(CLOCK_MONOTONIC, &m_time_func_ret_t1);                            \
    func_call;                                                                      \
    clock_gettime(CLOCK_MONOTONIC, &m_time_func_ret_t2);                            \
    (seconds_var) = (m_time_func_ret_t2.tv_sec - m_time_func_ret_t1.tv_sec) +       \
                    (m_time_func_ret_t2.tv_nsec - m_time_func_ret_t1.tv_nsec)/1e9;  \
} while(0)


int main(int argc, char * argv[]) {
    printf("Testing Vector memory pool\n");

    initialize_pool();

    const int max_trials = 10;
    double elapsed = 0.0;
    
    TIME_FUNC_RET(elapsed, sequential_borrow_yield(max_trials));
    printf("sequential_borrow_yield time: %.6f seconds\n", elapsed);

    elapsed = 0.0;
    TIME_FUNC_RET(elapsed, yield_sequential_after_borrow(max_trials));
    printf("yield_sequential_after_borrow time: %.6f seconds\n", elapsed);

    elapsed = 0.0;
    TIME_FUNC_RET(elapsed, yield_reverse_after_borrow(max_trials));
    printf("yield_reverse_after_borrow time: %.6f seconds\n", elapsed);

    elapsed = 0.0;
    TIME_FUNC_RET(elapsed, yield_last_borrowed(max_trials));
    printf("yield_last_borrowed time: %.6f seconds\n", elapsed);

    return 0;
}
