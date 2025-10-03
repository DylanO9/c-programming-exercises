#include <stdio.h>
#include <string.h>
#include <math.h>

void itoa(int n, char s[]);
void reverse(char s[]);

int main() {

    char s[100];
    int n = 2313;
    int largest_negative_number = -1 * pow(2,(sizeof(int)*8-1));
    itoa(largest_negative_number, s);
    printf("Number to convert: %d\n", largest_negative_number);
    printf("%s\n", s); 
}

void itoa(int n, char s[]) {
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
