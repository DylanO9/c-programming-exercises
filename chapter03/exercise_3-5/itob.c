#include <stdio.h>
#include <string.h>
#include <math.h>

/*
    Purpose: Write a function itob(n,s,b) that converts the integer n into a abase b character representation in the string s
*/

void itob(int n, char s[], int b);
void reverse(char s[]);

int main() {
    int n = 51;
    char s[1000];
    itob(n,s,2);
    printf("%s\n", s); 
    itob(n,s,3);
    printf("%s\n", s);
    int max_neg_int = -(pow(2, sizeof(int) * 8 - 1));
    itob(max_neg_int, s, 2);
    printf("%s\n", s);
}

void itob(int n, char s[], int b) {
    // The method to convert a base 10 to a base b is to divide by base b and save the 
    // remainders, then flip them reverse order to get the correct order
    int i = 0;
    unsigned int num;
    if (n < 0) {
        num = (unsigned)(-(long)n);
    } else {
        num = (unsigned)n;
    }
    while (num != 0) {
        int remainder = num % b;
        num /= b;
        s[i++] = remainder + '0';
    }
    if (n < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s); 
}

void reverse(char s[]) {
    int i = 0;
    int j = strlen(s) - 1;
    char temp;
    while (i < j) {
        temp = s[i];
        s[i++] = s[j];
        s[j--] = temp;
    }
}

