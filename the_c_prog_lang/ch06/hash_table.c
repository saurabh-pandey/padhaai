#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


#define MAX_SIZE 100

//------------------------------------------
// Test related data structures and Macros
//------------------------------------------

// Macro to define enum with a string map for better logging of the enums
#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,

// Operations on the hash table as enum items via a macro
#define FOREACH_OP(OP) \
    OP(INSERT) \
    OP(ERASE) \
    OP(FIND)


// Defining the Op enum
typedef enum {
    FOREACH_OP(GENERATE_ENUM)
} Op;


// Defining Op enum's string map
static const char * Op_Str[] = {
    FOREACH_OP(GENERATE_STRING)
};


// Operations on hash table are in 2 flavours:
// 1. Operations only involving the key i.e. find and erase
// 2. Operations involving both the key and value i.e. insert

// Key Only operation
typedef struct {
    Op op;
    char key[MAX_SIZE];
} OnlyKeyOp;

// Key and value based operation
typedef struct {
    Op op;
    char key[MAX_SIZE];
    char value[MAX_SIZE];
} KeyValOp;


// Any query to the hash table is either key-only op or key-value op
typedef union {
    OnlyKeyOp o_key_op;
    KeyValOp key_value_op;
} query;


// The 2 flavours of operations as enums via a macro
#define FOREACH_QUERY_TYPE(QUERY_TYPE) \
    QUERY_TYPE(ONLY_KEY) \
    QUERY_TYPE(KEY_VAL)


// Actual query type enum def.
typedef enum {
    FOREACH_QUERY_TYPE(GENERATE_ENUM)
} query_type;

// String map for query type enum
static const char * query_type_str[] = {
    FOREACH_QUERY_TYPE(GENERATE_STRING)
};


// A test is composed of the actual query and its type
typedef struct {
    query_type q_type;
    query q;
} test_data;

// TODO: How to check results of various operations in the tests?


// Helper macro to construct the query data structure
#define ONLY_KEY(op, key) {.q_type = ONLY_KEY, .q.o_key_op = {op, key}}
#define KEY_VAL(key, val) {.q_type = KEY_VAL, .q.key_value_op = {INSERT, key, val}}


//--------------------------------------
// Hash Table
//--------------------------------------

// An entry in the buckets
typedef struct hash_node {
    char key[MAX_SIZE];
    char value[MAX_SIZE];
    struct hash_node * next;
} HashNode;

#define MAX_BUCKET_SIZE 101

static HashNode * buckets[MAX_BUCKET_SIZE];

unsigned int hash(char *key) {
    unsigned int hash_value = 0;
    for (; key != NULL && *key != '\0'; ++key) {
        hash_value += *key + 31 * hash_value;
    }
    return hash_value % MAX_BUCKET_SIZE;
}


HashNode * find(char *key) {
    // TODO: Might also check size
    if (key == NULL) {
        return NULL;
    }
    HashNode * bucket_nodes = buckets[hash(key)];
    HashNode * current = bucket_nodes;
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            // Found
            return current;
        }
        current = current->next;
    }
    return NULL;
}


HashNode * erase(char *key) {
    // TODO: Might also check size 
    if (key == NULL) {
        return NULL;
    }
    HashNode * bucket_nodes = buckets[hash(key)];
    HashNode * prev = bucket_nodes;
    HashNode * current = bucket_nodes;
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            // Delete this node
            if (prev == NULL) {
                buckets[hash(key)] = current->next;
            } else {
                prev->next = current->next;
            }
            // Is this a good practice?
            current->next = NULL;
            return current;
        }
        current = current->next;
    }
    return NULL;
}

HashNode * insert(char *key, char * value) {
    // TODO: Might also check size
    if (key == NULL) {
        return NULL;
    }
    if (value == NULL) {
        return NULL;
    }

    HashNode * node = (HashNode *)malloc(sizeof(HashNode));
    strcpy(node->key, key);
    strcpy(node->value, value);
    const unsigned int bucket_index = hash(key);
    node->next = buckets[bucket_index];
    buckets[bucket_index] = node;
    
    return node;
}


int main() {
    bool debug = true;
    
    printf("Running tests for hash_table\n");

    test_data tests[] = {
        ONLY_KEY(FIND, "a"),
        KEY_VAL("a", "A"),
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
