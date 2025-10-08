#include <stdio.h>
#include <string.h>

/*
    Purpose: Write a recursive version of the function reverse(s)
*/

void reverse(char [], int i, int j);


int main() {
    char s[] = "Complicated String";
    printf("Original String: %s\n", s);
    int length = strlen(s) - 1;
    reverse(s, 0, length);
    printf("Reversed String: %s\n", s);
}

// i and j will be inclusive
void reverse(char s[], int i, int j) {
    if (i >= j) {
        return;
    }
    char temp = s[i];
    s[i] = s[j];
    s[j] = temp;
    
    reverse(s, i + 1, j - 1); 
}
