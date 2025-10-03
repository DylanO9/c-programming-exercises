#include <stdio.h>
#include <string.h>
#include <math.h>

/*
    Purpose: Extend the itoa function to handle the largest negative integer
            - Why does it not work for the original?
                - It does not work for the original because when you convert a negative number back to a positive there, there is a 1 integer difference.
                - Therefore, when converting from negative to positive there is an integer overflow, so to negate this we must convert to a long then an unsigned integer
*/

void itoa(int n, char s[], int w);
void reverse(char s[]);

int main() {

    char s[100];
    int n = 2313;
    int largest_negative_number = -1 * pow(2,(sizeof(int)*8-1));
    itoa(largest_negative_number, s, 50);
    printf("Number to convert: %d\n", largest_negative_number);
    printf("%sTest\n", s);
    itoa(n, s, 2);
    printf("Number to convert: %d\n", n);
    printf("%sTest\n", s); 
}

void itoa(int n, char s[], int w) {
    int i = 0;
    unsigned int num;
    if (n < 0) {
        num = (unsigned)(-(long)n);
    } else {
        num = (unsigned)n;
    }

    do {
        s[i++] = num % 10 + '0';
    } while ((num /= 10) > 0);
    
    if (n < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
    if (strlen(s) > w) {
        // We want to cut down s
        s[w] = '\0';
    } else {
        // Starting from strlen(s) we want to fill with pads up until w
        for (int x = strlen(s); x < w; x++) {
            s[x] = ' ';
        }
        s[w] = '\0';
    }
}

void reverse(char s[]) {
    int i = 0;
    int j = strlen(s) - 1;
    char temp;
    while (i < j) {
        temp = s[i];
        s[i] = s[j];
        s[j] = temp;
        i++;
        j--;
    }
}
