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
    int X;
    int y;
    int z;
} Vector;

#define MAX_POOL_SIZE 10

Vector pool[MAX_POOL_SIZE];

Vector * borrow(void) {
    return NULL;
}

void yield(Vector * v) {
}



int main(int argc, char * argv[]) {
    printf("Testing Vector memory pool\n");

    const int max_trials = 10;

    for (int i = 0; i < max_trials; ++i) {
        Vector * v = borrow();
        // Do something with v
        yield(v);
    }

    return 0;
}
