/*
    Purpose: Write a program to copy its input to its output, replacing each tab by \t, each backspace by \b and each backslash by \\. This makes tabs and backspaces visible in an unambiguous way.
*/

#include <stdio.h>

int main() {
    int c;
    
    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            fputs("\\t", stdout); 
        } else if (c == '\b') {
            fputs("\\b", stdout);   
        } else if (c == '\\') {
            fputs("\\\\", stdout);
        } else
            putchar(c);
    }
    putchar('\n');
}
