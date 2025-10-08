#include <stdio.h>
#include <limits.h>

/*
    Purpose: Adapt the ideas of printd to write a recursive version of itoa; that is, convert an integer into a string by calling a recursive routine
*/

void recursive_itoa(int n, char s[]);
void recursive_itoa_helper(unsigned int n, char s[], int *idx);

int main() {
    int n = INT_MIN;
    char s[23];
    int idx = 0;
    recursive_itoa(n, s);
    printf("Number to convert to string: %d\n", n);
    printf("String that was converted: %s\n", s);
}

void recursive_itoa(int n, char s[]) {
    int idx = 0;
    if (n < 0) 
        s[idx++] = '-';
    recursive_itoa_helper((unsigned int)n, s, &idx);    
    s[idx] = '\0';
}

void recursive_itoa_helper(unsigned int n, char s[], int *idx) {
    if (n / 10) 
        recursive_itoa_helper(n / 10, s, idx);
    s[(*idx)++] = n % 10 + '0';
}
