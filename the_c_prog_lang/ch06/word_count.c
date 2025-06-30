#include <stdio.h>
#include <string.h>
#include <ctype.h>

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


struct node {
    char *word;
    int count;
    struct node *left;
    struct node *right;
};

struct node * create_node(char *word) {
    return NULL;
}

struct node * add_node(char *word, struct node *root) {
    if (word == NULL) {
        // TODO: Should be a warning?
        return NULL;
    }
    
    if (root == NULL) {
        return create_node(word);
    } else {
        const int res = strcmp(root->word, word);
        if (res == 0) {
            ++(root->count);
        } else if (res < 0) {
            return add_node(word, root->left);
        } else {
            return add_node(word, root->left);
        }
    }
    
    return NULL;
}


void tree_print(struct node *root) {}


int main(int argc, char *argv[]) {
    printf("Count all words\n");
    char word[MAX_WORD_LEN] = "";
    int word_len = 0;
    struct node *root = NULL;
    while ((word_len = getword(word)) != EOF) {
        root = add_node(word, root);
        printf("%s\n", word);
    }

    tree_print(root);

    return 0;
}
