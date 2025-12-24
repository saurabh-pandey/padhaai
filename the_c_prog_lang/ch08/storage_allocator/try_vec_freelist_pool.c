#include "freelist_vec_pool.h"

#include <stdio.h>
#include <time.h>


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
        // print_vec(v);
        init_vec(v, i, i, i);
        // print_vec(v);
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
        // yield in the same order as borrowed
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
        int max_yield = 0;
        for (int j = 0; j < MAX_POOL_SIZE; ++j) {
            int num_yield = yield(last_borrowed);
            max_yield = num_yield > max_yield ? num_yield : max_yield;
            last_borrowed = borrow();
        }
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
