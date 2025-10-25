#include <stdio.h>
#include <ctype.h>

#define CHAR_LIMIT      100

int getword(char *, int);

int main() {
    char word[CHAR_LIMIT];
    while ((getword(word, CHAR_LIMIT)) != EOF) {
        printf("%s\n", word);
    }
    return 0;
}

int getword(char *word, int lim) {
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while(isspace(c = getch()))
        ;
    if (c != EOF)
        *w++ = c;
    if (c == '\"') {
        for (; --lim > 0 && (*w = getch()) != '\"'; w++) {
            if (*w == '\\') {
                *w = getch();
            }
        }
        *(++w) = '\0';
        return word[0];
    } else if (c == '/') {
        c = getch();
        *w++ = c;
        if (c == '/') {
            for ( ; --lim > 0 && (*w = getch()) != '\n'; w++) {
                
            }
            *w = '\0';
            return word[0];
        } else {
            ungetch(c);
            *w = '\0';
            return *w;
        } 
    } else if (!isalpha(c)) {
        *w = '\0';
        return c;
    } 
    for ( ; --lim > 0; w++)
        if (!isalnum(*w = getch()) && *w != '_') {
            ungetch(*w);
            break;
        }
    *w = '\0';
    return word[0];
}

char buf[100];
int buf_index = 0;

int getch(void) {
    if (buf_index == 0) {
        return getchar();
    } else {    
        return buf[--buf_index];
    } 
}

void ungetch(int c) {
    if (buf_index < 100) {
        buf[buf_index++] = c; 
    }
}
