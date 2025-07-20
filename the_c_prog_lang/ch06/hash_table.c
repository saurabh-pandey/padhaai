#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 100


typedef enum {
    INSERT,
    ERASE,
    FIND
} Op;


typedef struct {
    Op op;
    char key[MAX_SIZE];
} OnlyKeyOp;


typedef struct {
    Op op;
    char key[MAX_SIZE];
    char value[MAX_SIZE];
} KeyValOp;


typedef union {
    OnlyKeyOp o_key_op;
    KeyValOp key_value_op;
} test_data;

 // TODO: How to check results of various operations in the tests?


int main() {
    bool debug = false;
    
    printf("Running tests for hash_table\n");

    test_data tests[] = {
        {FIND, "a"},
        {INSERT, "a", "A"},
        {FIND, "a"},
        {ERASE, "a"},
        {FIND, "a"},
    };

    unsigned int num_failed = 0;
    for (int i = 0; i < sizeof(tests)/sizeof(test_data); ++i) {
    }
    if (num_failed > 0) {
        printf("%d test failed\n", num_failed);
    } else {
        printf("All tests passed\n");
    }
    printf("Done\n");

    return 0;
}
