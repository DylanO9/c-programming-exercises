#include <stdio.h>
#include <string.h>
/*
    Purpose: Create a function escape(s, t) that converts characters like newline and tab into visible escape sequences like \n and \t as it copies the string t to s. Use a switch.
    Write a function for the other direction as well, converting escape sequences into the real characters.
*/

void escape(char* s, char* t);

int main() { 
    char t[20] = "hi\n\t";
    char s[20];
    printf("T:%s\n", t);
    escape(s, t);
    printf("S:%s\n", s);
}

void escape(char* s, char* t) {
    int length = strlen(t);
    int placement = 0;
    for (int i = 0; i < length; i++) {
        switch (t[i]) {
            case '\t':
                s[placement++] = '\\';
                s[placement++] = 't'; 
                break;
            case '\n':
                s[placement++] = '\\';
                s[placement++] = 'n'; 
                break;
            default:
                s[placement++] = t[i];
        }
    } 
}
