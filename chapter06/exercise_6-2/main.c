#include <stdio.h>
#include <ctype.h>
#include <string.h>

/*
    Purpose: Write a program that reads a C program nad prints in alphabetical order each group of variable names that are identical in the first 6 characters
*/

int get_word(char *, int);
int get_word_skip(char *, int);
int read_program(int);
int is_datatype(char *);

char *datatypes[] = {"int", "long", "short", "float", "double", "char", NULL};

#define CHAR_LIMIT 100

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
    char *w = word;
    int waiting_for_variable = 0;
    while ((get_word_skip(w, CHAR_LIMIT) != EOF)) {
        if (waiting_for_variable) {
            if (strcmp(w, ";") == 0 || strcmp(w, "(") == 0) waiting_for_variable = 0;
            if (isalpha(*w)) printf("%s\n", w);
        } else if (is_datatype(w)) {
            waiting_for_variable = 1;
        }
    }
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
