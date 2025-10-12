#include <stdio.h>
#include <string.h>

/*
    Purpose: Write the function strend(s, t)
*/

int strend(char *s, char *t);

int main() {
    char *s = "Hello, there";
    char *t = "there";
    printf("String s: %s\n", s);
    printf("String t: %s\n", t);
    printf("Does string t occur at the end of string s? %d\n", strend(s, t));
}

int strend(char *s, char *t) {
    char *bs = s;
    char *bt = t;
    while (*bs)
        bs++;
    while (*bt)
        bt++; 
    while (bs > s && bt > t && *--bs == *--bt)
        ;
    if (bt == t)
        return 1;
    return 0;
}


