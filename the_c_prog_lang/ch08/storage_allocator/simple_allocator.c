#include "simple_allocator.h"

#include <stdio.h>
#include <unistd.h>

#define NALLOC 10

typedef union Header {
    struct {
        union Header * next;
        size_t sz;
    } s;
    max_align_t block;
} Header;

Header * freep = NULL;


void my_free(void * p) {
    // Find the block this memory belongs to and insert
    // The idea is that we have the current and next block in the existing list
    // And we have the new block to insert
    // New block is inserted in the right address
    // The new block is:
    // 1. Either supposed to be merged with curr
    // 2. Or is in between curr and next
    // 3. Or is merged with next
    // 4. Or search in the next pair
    // 5. If the new block address is less than curr that means it is the new head node
    Header * new_block = (Header *)p;
    Header * curr = freep;
    while (curr != NULL) {
        if (new_block < curr) {
            // This has to be new head node
            new_block->s.next = freep;
            freep = new_block;
            return;
        } else if (new_block == (curr + curr->s.sz)) {
            // Merge with curr
            // This means just increase the size of curr
            curr->s.sz += new_block->s.sz;
            // TODO: What if this new block make even curr and curr->next contiguous?
            // For now treating them as independent block which is slightly not optimal but still
            // works
            return;
        } else if (curr->s.next == NULL) {
            // Make it next block of curr
            curr->s.next = new_block;
            return;
        } else if ((new_block + new_block->s.sz) == curr->s.next) {
            // Merge with curr->next
            // Make curr->next point to new block
            // Make new block next point to curr->next->next
            // Update the size in new block header to be a sum of curr->next as well
            new_block->s.next = curr->s.next->s.next;
            new_block->s.sz += curr->s.sz;
            curr->s.next = new_block;
            return;
        } else if (new_block < curr->s.next) {
            // This is between curr and curr->next
            new_block->s.next = curr->s.next;
            curr->s.next = new_block;
            return;
        }
        curr = curr->s.next;
    }
    // If here then must likely head is NULL
    if (freep != NULL) {
        printf("Head was supposed to be NULL :(\n");
    }
    // In this case this is the new head
    freep = new_block;
}


void * morecore(size_t nunits) {
    void * new_mem = sbrk(nunits * sizeof(Header));
    if (new_mem == (void *)-1) {
        perror("sbrk failed");
        return NULL;
    }

    Header * new_block = (Header *)new_mem;
    new_block->s.sz = nunits;
    
    // Assign this to the list ordered by memory
    my_free(new_mem);
    
    return new_mem;
}


void * my_malloc(size_t nbytes) {
    const size_t nunits = (nbytes / sizeof(Header)) + 2;
    
    if (freep == NULL) {
        // This is the first call or everything was allocated
        freep = morecore(nunits);
    }
    
    // Need only 2 steps.
    // Step 1 if the first fit block is found in the existing list
    // Step 2 if nothing was found create a new one and return the block
    for (int i = 0; i < 2; ++i) {
        Header * curr = freep;
        Header * prev = NULL;
        while(curr != NULL) {
            if (curr->s.sz >= nunits) {
                // Found the first fit block
                if (curr->s.sz == nunits) {
                    // Size matches perfectly just plug out the block and return
                    if (prev != NULL) {
                        // Remove the block from the list
                        prev->s.next = curr->s.next;
                    } else {
                        // This was the first block so freep is pointing to the next one 
                        freep = curr->s.next;
                    }
                    return (void *)(curr + 1);
                } else {
                    // This block is bigger so resize and return the tail end
                    curr->s.sz -= nunits;
                    // TODO: Resize here
                }
            }
            curr = curr->s.next;
            prev = curr;
        }

        // If here then nothing of the right size was found
        // Add a block to the list
        morecore(nunits);
        // And search again
        // TODO: This is an overkill. I know this is the block to be returned so why search?
        // If we know curr and prev ptr then above loop can be used directly. Just reset curr and
        // prev to this new block and continue the loop
    }

    // Not enough memory so error case
    return NULL;
}
