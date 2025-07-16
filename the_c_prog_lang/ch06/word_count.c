#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <limits.h>


#define MAX_WORD_LEN 100


int getword(char *word) {
    char c = 0;
    int i = 0;
    while ((c = getchar()) != EOF) {
        if (isalpha(c)) {
            word[i] = c;
            ++i;
        } else {
            word[i] = '\0';
            return i;
        }
    }
    return EOF;
}


typedef struct node {
    char *word;
    int count;
    struct node *left;
    struct node *right;
} Node;


typedef struct list_node {
    Node * tree_node;
    struct list_node * next;
} ListNode;


Node * node_alloc() {
    return (Node *) malloc(sizeof(Node));
}


Node * create_node(char *word) {
    const size_t word_len = strlen(word);
    if (word_len == 0) {
        return NULL;
    }
    
    Node * new_node = node_alloc();
    if (new_node == NULL) {
        printf("ERROR: New node allocation failed\n");
        exit(1);
    }
    
    new_node->count = 1;
    new_node->left = NULL;
    new_node->right = NULL;
    
    char * new_word = (char *)malloc(sizeof(char) * (word_len + 1));
    if (new_word == NULL) {
        printf("ERROR: New word allocation failed\n");
        exit(1);
    }
    new_node->word = new_word;
    strcpy(new_node->word, word);
    
    return new_node;
}

Node * add_node(char *word, Node *root) {
    if (word == NULL) {
        // TODO: Should be a warning?
        return NULL;
    }
    
    if (root == NULL) {
        return create_node(word);
    } else {
        const int res = strcmp(word, root->word);
        if (res == 0) {
            ++(root->count);
        } else if (res < 0) {
            root->left = add_node(word, root->left);
        } else {
            root->right = add_node(word, root->right);
        }
    }
    
    return root;
}


void tree_print(Node *root) {
    if (root == NULL) {
        return;
    }
    tree_print(root->left);
    // printf("%s => count = %d, len = %zu\n", root->word, root->count, strlen(root->word));
    printf("%s => %d\n", root->word, root->count);
    tree_print(root->right);
}


void free_tree(Node * root) {
    if (root == NULL) {
        return;
    }

    free_tree(root->left);
    free_tree(root->right);
    free(root->word);
    free(root);
    root = NULL;
}


void tree_count_min_max(Node * root, int * min_count, int * max_count) {
    if (root == NULL) {
        return;
    }

    *min_count = root->count < *min_count ? root->count : *min_count;
    *max_count = root->count > *max_count ? root->count : *max_count;

    tree_count_min_max(root->left, min_count, max_count);
    tree_count_min_max(root->right, min_count, max_count);
}


void fill_count_ordered_nodes(Node * root, ListNode ** count_ordered_nodes) {
    if (root == NULL) {
        return;
    }

    ListNode * list_node = NULL;
    if (count_ordered_nodes[root->count - 1] == NULL) {
        list_node = (ListNode *)malloc(sizeof(ListNode));
        if (list_node == NULL) {
            printf("ERROR: Unable to allocate ListNode\n");
            return;
        }
        list_node->tree_node = root;
        list_node->next = NULL;
        count_ordered_nodes[root->count - 1] = list_node;
    } else {
        list_node = count_ordered_nodes[root->count - 1];
        while (list_node->next != NULL) {
            list_node = list_node->next;
        }
        list_node->next = (ListNode *)malloc(sizeof(ListNode));
        if (list_node->next == NULL) {
            printf("ERROR: Unable to allocate ListNode\n");
            return;
        }
        list_node->next->tree_node = root;
        list_node->next->next = NULL;
    }

    fill_count_ordered_nodes(root->left, count_ordered_nodes);
    fill_count_ordered_nodes(root->right, count_ordered_nodes);
}

void print_count_ordered_nodes(ListNode ** count_ordered_nodes, int size) {
    if (count_ordered_nodes == NULL) {
        return;
    }

    for (int i = 0; i < size; ++i) {
        ListNode * list_node = count_ordered_nodes[i];
        if (list_node != NULL) {
            printf("Count = %d, ", i + 1);
            printf("Nodes = [");
            while (list_node != NULL) {
                printf("%s", list_node->tree_node->word);
                if (list_node->next != NULL) {
                    printf(", ");
                }
                list_node = list_node->next;
            }
            printf("]\n");            
        }
    }
}

void free_list_nodes(ListNode ** list_node) {
    if (list_node == NULL) {
        return;
    }

    if (*list_node == NULL) {
        return;
    }

    free_list_nodes(&((*list_node)->next));
    free(*list_node);
    *list_node = NULL;
}


void tree_print_by_count_decreasing(Node * root) {
    if (root == NULL) {
        return;
    }
    
    int min_count = INT_MAX;
    int max_count = INT_MIN;

    tree_count_min_max(root, &min_count, &max_count);
    printf("min_count = %d, max_count = %d\n", min_count, max_count);

    if (min_count > max_count) {
        printf("ERROR: min word count (%d) is bigger than max word count (%d)\n",
               min_count,
               max_count);
        return;
    }

    const int arr_sz = max_count - min_count + 1;

    ListNode ** count_ordered_nodes = (ListNode **)malloc(sizeof(ListNode *) * arr_sz);
    if (count_ordered_nodes == NULL) {
        printf("ERROR: Allocation of count ordered nodes failed\n");
        return;
    }

    // Initialize
    for (int i = 0; i < arr_sz; ++i) {
        count_ordered_nodes[i] = NULL;
    }

    fill_count_ordered_nodes(root, count_ordered_nodes);

    print_count_ordered_nodes(count_ordered_nodes, arr_sz);

    // Free all nodes
    for (int i = 0; i < arr_sz; ++i) {
        if (count_ordered_nodes[i] != NULL) {
            free_list_nodes(&(count_ordered_nodes[i]));
            // free(count_ordered_nodes[i]);
            printf("%d => %p\n", i, count_ordered_nodes[i]);
        }
    }
    if (count_ordered_nodes != NULL) {
        free(count_ordered_nodes);
    }
}


int main(int argc, char *argv[]) {
    printf("Count all words\n");
    
    char word[MAX_WORD_LEN] = "";
    int word_len = 0;
    Node * root = NULL;

    while ((word_len = getword(word)) != EOF) {
        root = add_node(word, root);
        // printf("%s\n", word);
        
    }

    int print_count_based = 0;
    if (argc > 1 && strcmp(argv[1], "--count") == 0) {
        print_count_based = 1;
    }

    if (print_count_based == 0) {
        printf("Tree based view\n");
        tree_print(root);
    } else {
        printf("Count based view\n");
        tree_print_by_count_decreasing(root);
    }

    printf("Done\n");

    free_tree(root);

    return 0;
}
