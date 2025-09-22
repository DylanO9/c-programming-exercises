#include <stdio.h>

/*
    Purpose: Write a function invert(x, p, n) that returns x with the n bits that begin at position p inverted
*/

unsigned invert(unsigned x, int p, int n);
unsigned getbits(unsigned x, int p, int n);

int main() {
    unsigned x = 38;
    printf("%u\n", invert(38, 2, 2));
}

unsigned invert(unsigned x, int p, int n) {
    unsigned mask = (((1 << n) - 1) << p + 1 - n);
    return x ^ mask;
}

unsigned getbits(unsigned x, int p, int n) {
    return (x >> (p + 1 - n)) & ~(~0 << n);
}

