#include <stdio.h>
#include <string.h>

/*
    Purpose: Write versions of the library functions strncpy, strncat, and strncmp, which operate on at most the first n characters of their argument strings
*/

void my_strncpy(char *s, char *t, int n);
void my_strncat(char *s, char *t, int n);
int my_strncmp(char *s, char *t, int n);

int main() {
    
    // Test strncpy
    char s[] = "Hello there!";
    char t[] = "Hi";
    printf("S: %s\n", s);
    printf("T: %s\n", t);
    my_strncpy(s, t, 2);
    printf("strncpy result: %s\n", s);
    
    // Test strncat
    char cat_s[20] = "Hello";
    char cat_t[] = " there";
    printf("S: %s\n", cat_s);
    printf("T: %s\n", cat_t);
    my_strncat(cat_s, cat_t, 10);
    printf("strncat result: %s\n", cat_s);

    // Test strncmp
    char cmp_s[] = "Helpo";
    char cmp_t[] = "Heloo";
    printf("S: %s\n", cmp_s);
    printf("T: %s\n", cmp_t);
    int cmp = my_strncmp(cmp_s, cmp_t, 4);
    printf("strncmp result: %d\n", cmp); 
}


void my_strncpy(char *s, char *t, int n) {
    while (n-- > 0 && (*s++ = *t++) != '\0')
        ;
    while (n-- > 0) 
        *s++ = '\0';
}
void my_strncat(char *s, char *t, int n) {
    while (*s)
        s++;
    while (n-- > 0 && *t != '\0')
        *s++ = *t++;
    *s = '\0';    
}
int my_strncmp(char *s, char *t, int n) {
    for (; n > 0 && *s == *t; n--, s++, t++)
        if (*s == '\0')
            return 0;
    return (n == 0) ? 0 : (unsigned char)*s - (unsigned char)*t;
}
