#include <stdio.h>

/*
    Purpose: Create a program that returns the first location in a string s1
    where any character from string s2 occurs
*/

int any(char s1[], char s2[]);

int main() {
    char s1[20] = "Hi there!";
    char s2[20] = "iwz";

    printf("Original String:%s\n", s1);
    printf("Characters to look for:%s\n", s2);
    printf("Index of first character found:%d\n", any(s1, s2));
}

int any(char s1[], char s2[]) {
    int i = 0;
    while (s1[i] != '\0') {
        for (int j = 0; s2[j] != '\0'; j++) {
            if (s2[j] == s1[i]) {
                return i;
            }
        }
        i++;
    }
    return -1;
}

