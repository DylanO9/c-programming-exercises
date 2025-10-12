#include <stdio.h>
/*
    Purpose: Write a pointer version of the function strcat
*/

void my_strcat(char *s, char *t);

int main() {
    char s[30] = "Hello, ";
    char t[] = "there";
    my_strcat(s, t);
    printf("Concantenated String: %s\n", s);
}

// Concantenate t to the end of s; We assume that s has enough space to hold t
void my_strcat(char *s, char *t) {
    for (; *s != '\0'; s++)
        ;
    while((*s++ = *t++) != '\0')
        ;
}
