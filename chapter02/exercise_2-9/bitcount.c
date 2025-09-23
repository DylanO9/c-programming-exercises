#include <stdio.h>

/*
    Purpose: Write a faster version of bitcount using x &= (x-1)
*/

int main() {
    
    unsigned x = 100;
    int ones_count = 0;
    printf("Original x:%u\n", x); 
    while (x != 0) {
        x &= (x-1);
        ones_count++;
    }
    
    printf("The number of ones in x:%d\n", ones_count);
}
