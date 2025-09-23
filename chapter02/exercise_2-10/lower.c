#include <stdio.h>

int lower(int x);

int main() {
    char x = 'T';
    printf("The uppercase letter: %c\n", x);
    printf("The lowercased version: %c\n", lower(x));
    char y = 't';
    printf("The uppercase letter: %c\n", y);
    printf("The lowercased version: %c\n", lower(y));

    return 0; 
}

int lower(int x) {
    return x >= 'A' && x <= 'Z' ? x + ('a' - 'A') : x;
}
