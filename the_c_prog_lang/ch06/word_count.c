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


void tree_print_by_count_decreasing(Node * root) {
    if (root == NULL) {
        return;
    }
    
    int min_count = INT_MAX;
    int max_count = INT_MIN;

    tree_count_min_max(root, &min_count, &max_count);
    printf("min_count = %d, max_count = %d\n", min_count, max_count);
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

    tree_print(root);

    tree_print_by_count_decreasing(root);

    free_tree(root);

    return 0;
}
