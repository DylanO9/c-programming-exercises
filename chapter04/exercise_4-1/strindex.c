#include <stdio.h>
#include <string.h>
/*
    Purpose: Write the function strindex(s,t) which returns the position of the rightmost occurrence of t in s, or -1 if there is none
*/

int strindex(char s[], char t[]);

int main() {
    char s[] = "Hello, my name is Dylan OliHevares";
    char t[] = "He";
    printf("%d\n", strindex(s, t));
}

int strindex(char s[], char t[]) {
    int saved_index = -1;
    int i, j, k;
    for (i = 0; s[i] != '\0'; i++) {
        for (j = i, k = 0; t[k] != '\0' && t[k] == s[j]; k++, j++);
        if (t[k] == '\0') {
            saved_index = i;
        }
    }
    return saved_index;
}
