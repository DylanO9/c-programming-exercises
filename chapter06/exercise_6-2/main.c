#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define CHAR_LIMIT  100
#define MAX_WORDS   10

/*
    Purpose: Write a program that reads a C program nad prints in alphabetical order each group of variable names that are identical in the first 6 characters
*/

typedef struct tree_node {
    char first;
    struct list_node *head; 
    struct tree_node *left;
    struct tree_node *right;
} tree_node;

typedef struct list_node {
    char word[CHAR_LIMIT];
    struct list_node *next; 
} list_node;

int get_word(char *, int);
int get_word_skip(char *, int);
int read_program(int);
int is_datatype(char *);
tree_node *add_to_tree(char *, tree_node *);
void in_order_traversal(tree_node *);


char *datatypes[] = {"int", "long", "short", "float", "double", "char", NULL};


int main() {
    read_program(0);
}

int read_program(int prefix_len) {
    /*
        Flow:
        - Process words
        - Identify if a word we are looking at is_datatype
        - If it is a datatype, then wait for the next token
        
        - How do we know which tokens are variables?
        - The token directly after an is_datatype
            - If we are in this waiting_for_variable state, then any token after a , is what we want as well
        - We stop the waiting-for_variable state when we see a ;
    */
    char word[CHAR_LIMIT];
    int waiting_for_variable = 0;
    tree_node *root = NULL;
    printf("Variables:\n");
    while ((get_word_skip(word, CHAR_LIMIT) != EOF)) {
        if (waiting_for_variable) {
            if (strcmp(word, ";") == 0 || strcmp(word, "(") == 0) waiting_for_variable = 0;
            if (isalpha(*word)) {
                if (root == NULL) {
                    root = add_to_tree(word, root); 
                } else {
                    add_to_tree(word, root);
                }
                printf("%s\n", word);
            } 
        } else if (is_datatype(word)) {
            waiting_for_variable = 1;
        }
    }
    if (root != NULL) {
        printf("Groups: \n");
        in_order_traversal(root);
    }
}

void in_order_traversal(tree_node *root){
    /*
        Flow:
        - Left, Curr, Right
        - Print the first character, followed by the list of words it has
    */
    if (root == NULL) {
        return;    
    }
    in_order_traversal(root->left);
    
    list_node *curr = root->head;
    printf("%c: ", root->first);
    list_node *prev = root->head;
    while (curr != NULL) {
        printf(" %s", curr->word);
        curr = curr->next;
        free(prev);
        prev = curr;
    }
    printf("\n");
 
    in_order_traversal(root->right);  
    free(root);
}

tree_node *add_to_tree(char *word, tree_node *root) {
    /*
        Flow:
        - Find the spot the first n letters of this word should be located in the tree
        - If a tree_node exists, then create a list_node for the word, and add it to the linked_list
        - If a tree_node does not exist, then create a node link it, then create a list_node and add it as the head
    */
    if (root == NULL) {
        tree_node *new_tree_node = (tree_node *) malloc(sizeof(tree_node));
        new_tree_node->left = NULL;
        new_tree_node->right = NULL;
        new_tree_node->first = *word; 

        // Create a new list_node
        list_node *new_list_node = (list_node *) malloc(sizeof(list_node));
        new_list_node->next = NULL;
        strcpy(new_list_node->word, word); 
        new_tree_node->head = new_list_node;
        return new_tree_node;
    } else if (root->first == *word) {
        // We've found the tree_node that should have this word
        printf("%c\n", root->first);
        list_node *new_list_node = (list_node *) malloc(sizeof(list_node));
        new_list_node->next = NULL;
        strcpy(new_list_node->word, word);
        
        list_node *curr = root->head;
        while (curr->next != NULL)
            curr = curr->next;
        
        curr->next = new_list_node;   
        return root;
    }
    
    int compare = *word - root->first;
    if (compare > 0) {
        // The node we are looking for is on the right
        root->right = add_to_tree(word, root->right);   
    } else if (compare < 0) {
        // The node we are looking for is on the left
        root->left = add_to_tree(word, root->left);
    } 
    
    return root; 
}

int get_word(char *word, int lim) {
    /*
        Flow:
        - Skip over all whitespace preceding
        - Check if we are at an EOF
        - Check if is not alpha or _ meaning that we are not at a variable
        - Keep reading variable, then ungetc when we overflow
    */
    char *w = word;
    int c;
    
    while (isspace(c = getchar()))
        ;

    if (c != EOF)
        *w++ = c;    
    
    if (!isalpha(c) && c != '_') {
        *w = '\0';
        return c;
    }
    
    for (; --lim > 0; w++) {
        if (!isalpha(*w = getchar()) && *w != '_') {
            ungetc(*w, stdin);
            break;
        } 
    }
    *w = '\0';
    return word[0];
}

int get_word_skip(char *word, int lim) {
    /*
        Flow:
        - We want to skip over single line comments
        - We want to skip over multi-line comments
        - We want to skip over quotes
    */
    int c, d;
    while((c = get_word(word, lim)) != EOF) {
        if (c == '/') {
            if ((d = getchar()) == '/') {
                while ((c = getchar()) != '\n' && c != EOF)
                   ; 
            } else if (d == '*') {
                while ((c = getchar()) != EOF) {
                    if (c == '*' && (d = getchar()) == '/') {
                        break;
                    }
                }
            } else {
                ungetc(d, stdin);
            }
        } else if (c == '\"') {
            while ((c = getchar()) != EOF && c != '\"') {
                if (c == '\\') getchar();
            }
        } else {
            return c;
        }
    }
    return EOF;
}

int is_datatype(char *word) {
    /*
        Flow:
        - Iterate through datatypes array, and strcmp
    */
    
    char **dt_iter = datatypes;
    for (; *(dt_iter) != NULL; dt_iter++) {
        if (strcmp(*dt_iter, word) == 0) {
            return 1;
        }
    } 

    return 0; 
}
