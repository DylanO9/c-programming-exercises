#include <stdio.h>

// Modes
#define NORMAL_MODE                 0
#define STRING_MODE                 1
#define CHARACTER_MODE              2
#define SINGLE_COMMENT_MODE         3
#define MULTILINE_COMMENT_MODE      4

int main() {
    int c;
    int mode = NORMAL_MODE;
    while ((c = getchar()) != EOF) {
        if (mode == NORMAL_MODE) {
            if (c == '/') {
                // Must pull the next character to confirm what group it is in
                c = getchar();
                
                if (c == EOF) {
                    return 0;
                }
                
                if (c == '/') {
                    mode = SINGLE_COMMENT_MODE;
                }   
                else if (c == '*') {
                    mode = MULTILINE_COMMENT_MODE;
                }
                else {
                    putchar('/');
                    putchar(c);
                }
                continue;
            }
            if (c == '\"') {
                putchar(c);
                mode = STRING_MODE;
            }
            else if (c == '\'') {
               putchar(c);
               mode = CHARACTER_MODE;
            }
            else {
                putchar(c);
            }
        }
        else if (mode == STRING_MODE) {
            if (c == '/') {
                putchar(c);
                c = getchar();
                if (c == EOF) {
                    return 0;
                }
                putchar(c);
            }
            else if (c == '\"') {
                putchar(c);
                mode = NORMAL_MODE;
            }
            else {
                putchar(c);    
            }
        }
        else if (mode == CHARACTER_MODE) {
            if (c == '/') {
                putchar(c);
                c = getchar();
                if (c == EOF) {
                    return 0;
                }
                putchar(c);
            }
            else if (c == '\'') {
                putchar(c);
                mode = NORMAL_MODE;
            }
            else {
                putchar(c);
            }
        }
        else if (mode == SINGLE_COMMENT_MODE) {
            if (c == '\n') {
                mode = NORMAL_MODE;
            }
        }
        else if (mode == MULTILINE_COMMENT_MODE) {
            if (c == '*') {
                // We want to look for the / to see if the multiline comment has ended
                c = getchar();
               
                if (c == EOF) {
                    return 0;
                }

                if (c == '/') {
                    mode = NORMAL_MODE;
                }
            }
        }     
    }
    return 0; 
}
