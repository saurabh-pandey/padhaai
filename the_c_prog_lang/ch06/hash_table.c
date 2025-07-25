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

// A linked list node in the buckets
typedef struct node_list {
    char *key;
    char *value;
    struct node_list * next;
} NodeList;

#define MAX_BUCKET_SIZE 5

static NodeList * buckets[MAX_BUCKET_SIZE];


NodeList * alloc_node(const char * key, const char * value) {
    NodeList * node = (NodeList *)malloc(sizeof(NodeList));
    if (node == NULL) {
        printf("ERROR: Allocating NodeList\n");
        return NULL;
    }
    node->key = strdup(key);
    node->value = strdup(value);
    node->next = NULL;
    return node;
}

void free_node(NodeList ** node) {
    if (node == NULL) {
        return;
    }

    if (*node == NULL) {
        return;
    }

    NodeList * curr_node = *node;
    
    free_node(&(curr_node->next));

    free(curr_node->key);
    free(curr_node->value);
    curr_node->key = NULL;
    curr_node->value = NULL;
    curr_node->next = NULL;
    free(curr_node);
    *node = NULL;
}


unsigned int hash(const char *key) {
    unsigned int hash_value = 0;
    for (; key != NULL && *key != '\0'; ++key) {
        hash_value += *key + 31 * hash_value;
    }
    return hash_value % MAX_BUCKET_SIZE;
}


NodeList * find(const char *key) {
    if (strlen(key) == 0) {
        return NULL;
    }
    
    NodeList * bucket_node = buckets[hash(key)];
    while (bucket_node != NULL) {
        if (strcmp(bucket_node->key, key) == 0) {
            // Found
            return bucket_node;
        }
        bucket_node = bucket_node->next;
    }
    return NULL;
}


NodeList * erase(const char *key) { 
    if (strlen(key) == 0) {
        return NULL;
    }
    
    NodeList * bucket_node = buckets[hash(key)];
    NodeList * prev = NULL;
    while (bucket_node != NULL) {
        if (strcmp(bucket_node->key, key) == 0) {
            // Delete this node
            if (prev == NULL) {
                buckets[hash(key)] = bucket_node->next;
            } else {
                prev->next = bucket_node->next;
            }
            // Is this a good practice?
            bucket_node->next = NULL;
            return bucket_node;
        }
        prev = bucket_node;
        bucket_node = bucket_node->next;
    }
    return NULL;
}

NodeList * insert(const char *key, const char * value) {
    if (strlen(key) == 0) {
        return NULL;
    }
    if (strlen(value) == 0) {
        return NULL;
    }

    NodeList * node = find(key);
    if (node != NULL) {
        free(node->value);
        node->value = strdup(value);
    } else {
        node = alloc_node(key, value);
        const unsigned int bucket_index = hash(key);
        node->next = buckets[bucket_index];
        buckets[bucket_index] = node;
    }
    
    return node;
}

void free_all_buckets(void) {
    for (int i = 0; i < MAX_BUCKET_SIZE; ++i) {
        free_node(&buckets[i]);
    }
}

void print_node(NodeList * node) {
    if (node != NULL) {
        printf("(%s, %s)", node->key, node->value);
    } else {
        printf("(NULL)");
    }
}

void print_all_buckets(void) {
    for (int i = 0; i < MAX_BUCKET_SIZE; ++i) {
        printf("Bucket[%d] = [", i);
        NodeList * node = buckets[i];
        if (node != NULL) {
            while (node != NULL) {
                print_node(node);
                if (node->next != NULL) {
                    printf(", ");
                }
                node = node->next;
            }
        } else {
            printf("NULL");
        }
        printf("]\n");
    }
}


void print_hash_table(void) {
    printf("Hash Table = {");
    for (int i = 0; i < MAX_BUCKET_SIZE; ++i) {
        // printf("Bucket[%d] = [", i);
        NodeList * node = buckets[i];
        if (node != NULL) {
            while (node != NULL) {
                print_node(node);
                if (node->next != NULL) {
                    printf(", ");
                }
                node = node->next;
            }
        }
        if (i != MAX_BUCKET_SIZE - 1) {
            printf(", ");
        }
    }
    printf("}\n");
}

void do_only_key_op(OnlyKeyOp only_key_op) {
    switch (only_key_op.op)
    {
        case FIND:
        {
            NodeList * found_node = find(only_key_op.key);
            printf("FOUND = ");
            print_node(found_node);
            printf("\n");
            break;
        }
        case ERASE:
        {
            NodeList * erased_node = erase(only_key_op.key);
            printf("ERASED = ");
            print_node(erased_node);
            printf("\n");
            free_node(&erased_node);
            break;
        }
        default:
        {
            printf("ERROR: Unsupported key only operation %s\n", Op_Str[only_key_op.op]);
            break;
        }
    }
}

void do_key_val_op(KeyValOp key_val_op) {
    switch (key_val_op.op)
    {
        case INSERT:
        {
            NodeList * inserted_node = insert(key_val_op.key, key_val_op.value);
            printf("INSERTED = ");
            print_node(inserted_node);
            printf("\n");
            break;
        }
        default:
        {
            printf("ERROR: Unsupported key value operation %s\n", Op_Str[key_val_op.op]);
            break;
        }
    }
}

void do_op(test_data op_query) {
    switch (op_query.q_type)
    {
        case ONLY_KEY:
        {
            printf("q_type = %s, op = %s, key = %s\n",
                    query_type_str[op_query.q_type],
                    Op_Str[op_query.q.o_key_op.op],
                    op_query.q.o_key_op.key);
            do_only_key_op(op_query.q.o_key_op);
            break;
        }
        case KEY_VAL:
        {
            printf("q_type = %s, op = %s, key = %s, val = %s\n",
                    query_type_str[op_query.q_type],
                    Op_Str[op_query.q.key_value_op.op],
                    op_query.q.key_value_op.key,
                    op_query.q.key_value_op.value);
            do_key_val_op(op_query.q.key_value_op);
            break;
        }
    
        default:
        {
            printf("ERROR: Unsupported query %s\n", query_type_str[op_query.q_type]);
            break;
        }
    }
}


int main() {
    bool debug = true;
    
    printf("Running tests for hash_table\n");

    test_data tests[] = {
        ONLY_KEY(FIND, "a"),
        KEY_VAL("a", "A"),
        ONLY_KEY(ERASE, "a"),
        KEY_VAL("a", "A"),
        KEY_VAL("b", "B"),
        KEY_VAL("c", "C"),
        KEY_VAL("d", "D"),
        KEY_VAL("e", "E"),
        KEY_VAL("f", "F"),
        KEY_VAL("g", "G"),
        KEY_VAL("i", "I"),
        KEY_VAL("j", "J"),
        KEY_VAL("k", "K"),
        KEY_VAL("l", "L"),
        ONLY_KEY(ERASE, "f"),
        ONLY_KEY(ERASE, "b"),
    };

    unsigned int num_failed = 0;
    for (int i = 0; i < sizeof(tests)/sizeof(test_data); ++i) {
        if (debug) {
            do_op(tests[i]);
            // print_all_buckets();
            print_hash_table();
        }
    }
    
    if (num_failed > 0) {
        printf("%d test failed\n", num_failed);
    } else {
        printf("All tests passed\n");
    }

    print_all_buckets();
    printf("Done\n");

    free_all_buckets();

    print_all_buckets();

    return 0;
}
