#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 100


// typedef enum {
//     INSERT,
//     ERASE,
//     FIND
// } Op;

// static const char * Op_Str[] = {"INSERT", "ERASE", "FIND"};

#define FOREACH_OP(OP) \
    OP(INSERT) \
    OP(ERASE) \
    OP(FIND)

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,

typedef enum {
    FOREACH_OP(GENERATE_ENUM)
} Op;

static const char * Op_Str[] = {
    FOREACH_OP(GENERATE_STRING)
};

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
} query;


typedef enum {
    ONLY_KEY,
    KEY_VAL
} query_type;

static const char * query_type_str[] = {"ONLY_KEY", "KEY_VAL"};


typedef struct {
    query_type q_type;
    query q;
} test_data;

 // TODO: How to check results of various operations in the tests?

 #define ONLY_KEY(op, key) {.q_type = ONLY_KEY, .q.o_key_op = {op, key}}
 #define KEY_VAL(key, val) {.q_type = KEY_VAL, .q.key_value_op = {INSERT, key, val}}


int main() {
    bool debug = true;
    
    printf("Running tests for hash_table\n");

    test_data tests[] = {
        // {.q_type = ONLY_KEY, .q.o_key_op = {FIND, "a"}},
        ONLY_KEY(FIND, "a"),
        // {.q_type = KEY_VAL, .q.key_value_op = {INSERT, "a", "A"}},
        KEY_VAL("a", "A"),
        // {.q_type = ONLY_KEY, .q.o_key_op = {ERASE, "a"}},
        ONLY_KEY(ERASE, "a"),
    };

    unsigned int num_failed = 0;
    for (int i = 0; i < sizeof(tests)/sizeof(test_data); ++i) {
        if (debug) {
            switch (tests[i].q_type)
            {
                case ONLY_KEY:
                {
                    printf("q_type = %s, op = %s, key = %s\n",
                           query_type_str[tests[i].q_type],
                           Op_Str[tests[i].q.o_key_op.op],
                           tests[i].q.o_key_op.key);
                    break;
                }
                case KEY_VAL:
                {
                    printf("q_type = %s, op = %s, key = %s, val = %s\n",
                           query_type_str[tests[i].q_type],
                           Op_Str[tests[i].q.key_value_op.op],
                           tests[i].q.key_value_op.key,
                           tests[i].q.key_value_op.value);
                    break;
                }
            
                default:
                {
                    printf("ERROR: Unsupported operation %d\n", tests[i].q_type);
                    break;
                }
            }
        }
    }
    if (num_failed > 0) {
        printf("%d test failed\n", num_failed);
    } else {
        printf("All tests passed\n");
    }
    printf("Done\n");

    return 0;
}
