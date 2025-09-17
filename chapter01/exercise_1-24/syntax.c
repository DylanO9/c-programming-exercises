#include <stdio.h>

#define NORMAL_MODE                 0
#define SINGLE_QUOTE_MODE           1
#define DOUBLE_QUOTE_MODE           2
#define SINGLE_COMMENT_MODE        3
#define MULTILINE_COMMENT_MODE      4

/*
    Purpose:
    Check for rudimentary syntax errors like unmatched parentheses, brackets, and braces.
    Account for double quotes, single quotes, escape sequences, and comments.
*/


int main() {
    char stack[1000];
    int curr_pos = 0; // Where do we place the next character
    int c;
    int mode = NORMAL_MODE;

    while ((c = getchar()) != EOF) {
        if (mode == NORMAL_MODE) {
            // Let's account for the different chars we can get
            if (c == '{' || c == '[' || c == '(') {
                // Place it on the stack
                stack[curr_pos] = c;
                curr_pos++;
            }
            else if (c == '}') {
                // Make sure that the top of the stack is a closing
                if (curr_pos == 0 || stack[curr_pos - 1] != '{') {
                    printf("Closing curly brace seen with no opening\n");
                } 
                // Remove the top of the stack
                else if (curr_pos != 0 && stack[curr_pos - 1] == '{') {
                    stack[curr_pos - 1] = ' ';
                    curr_pos--;
                }
            }
            else if (c == ']') {
                // Make sure that the top of the stack is a closing
                if (curr_pos == 0 || stack[curr_pos - 1] != '[') {
                    printf("Closing bracket seen with no opening\n");
                } 
                // Remove the top of the stack
                else if (curr_pos != 0 && stack[curr_pos - 1] == '[') {
                    stack[curr_pos - 1] = ' ';
                    curr_pos--;
                }
            }
            else if (c == ')') {
                // Make sure that the top of the stack is a closing
                if (curr_pos == 0 || stack[curr_pos - 1] != '(') {
                    printf("Closing parenthesis seen with no opening\n");
                } 
                // Remove the top of the stack
                else if (curr_pos != 0 && stack[curr_pos - 1] == '(') {
                    stack[curr_pos - 1] = ' ';
                    curr_pos--;
                }
            }
            else if (c == '\''){
                mode = SINGLE_QUOTE_MODE;
            }
            else if (c == '"') {
                mode = DOUBLE_QUOTE_MODE;
            }
            else if (c == '/') {
                // Grab another character to see if this should be sent to single or multiline comments
                if ((c = getchar()) != EOF) {
                    if (c == '/') {
                        mode = SINGLE_COMMENT_MODE;
                    }
                    else if (c == '*') {
                        mode = MULTILINE_COMMENT_MODE;
                    }
                }
                
            }
        } 
        else if (mode == SINGLE_QUOTE_MODE) {
            if (c == '\\') {
                // Grab another character but ignore
                if ((c = getchar()) == EOF) {
                    return 0;
                }
            }
            else if (c == '\'') {
                mode = NORMAL_MODE;
            }
        }
        else if (mode == DOUBLE_QUOTE_MODE) {
            if (c == '\\') {
                if ((c = getchar()) == EOF) {
                    return 0;
                }
            }
            else if (c == '"') {
                mode = NORMAL_MODE;
            }
        }
        else if (mode == SINGLE_COMMENT_MODE) {
            if (c == '\n') {
                mode = NORMAL_MODE;
            } 
        }
        else if (mode == MULTILINE_COMMENT_MODE) {
            if (c == '*') {
                if ((c = getchar()) == EOF) {
                    return 0;
                }
                if (c == '/') {
                    mode = NORMAL_MODE;
                } 
            }
        }
    }

    if (curr_pos != 0) {
        for (int i = 0; i < curr_pos; i++) {
            printf("Missing a matching symbol for %c\n", stack[i]);
        }
    }



     return 0;
}
