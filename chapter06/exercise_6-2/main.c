#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define NORMAL              1
#define QUOTES              2
#define COMMENT             3
#define MULTI_COMMENT       4
#define VARIABLE            5

void process_token();
void read_program();
int is_datatype(const char *word); 

const char *datatypes[] = {
    "int", "long", "short", "float", "double", "char"    
};

struct list_node {
    char *word;
    struct list_node *node;
};

struct tree_node {
    char *first_six;
    struct tree_node *left_node;
    struct tree_node *right_node;
};

int main() {
   read_program(); 
}

char token[40];
int token_idx;    
char prev_token[40] = "\0";

void read_program() {
    int state = NORMAL;
    int c;

    while((c = getchar()) != EOF) {
        switch (state) {
            case VARIABLE:
                // This next token should be a variable name, there can be more if extra , so read tokens until a ; or =
                token[0] = '\0';
                token_idx = 0; 
                if (isalpha(c)) {
                    token[token_idx++] = c;
                    token[token_idx] = '\0';
                }
                else if (c == ' ') {
                    // Add to the binary tree
                    printf("%s\n", token);
                    token[0] = '\0';
                    token_idx = 0;
                }

                else if (c == ';' || c == '=') {
                    // This is the end of variable mode
                    printf("%s\n", token);
                    token[0] = '\0';
                    token_idx = 0;
                    state = NORMAL;
                }
                break;
            case NORMAL:
                if (c == '\n' || c == ' ' || c == '\t' || c == '\r' || c == '\v' || c == '\f') {
                    token[token_idx++] = '\0';
                    
                    if (is_datatype(token)) {
                        state = VARIABLE; 
                    }
                }
                else if (c == '/') {
                    c = getchar();
                    if (c == '/') {
                        state = COMMENT;
                    } 
                    else if (c == '*') {
                        state = MULTI_COMMENT;
                    }    
                    else {
                        putchar(c);
                    }
                }
                else if (c == '\"') {
                    state = QUOTES;
                }
                else {
                    token[token_idx++] = c;        
                }
                break;
            case QUOTES:
                // Ignore inside, but if we see another " with no \ beforehand, then end
                if (c == '\\') {
                    c = getchar();
                    if (c == '\"') {
                        state = NORMAL;
                    }
                }
                break;
            case COMMENT:
                if (c == '\n') {
                    state = NORMAL;
                }
                break;
            case MULTI_COMMENT:
                if (c == '*') {
                    c = getchar();
                    if (c == '/') {
                        state = NORMAL;
                    } 
                    else {
                        putchar(c);
                    }
                }
                break;
        }    
    } 
}


//void add_to_tree(char var_name[20]) {
//}

int is_datatype(const char *word) {
    for (int i = 0; datatypes[i] != NULL; i++) {
        if (strcmp(word, datatypes[i]) == 0)
            return 1;
    }
    return 0;
}

