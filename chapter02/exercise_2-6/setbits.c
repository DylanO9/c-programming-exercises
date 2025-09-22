#include <stdio.h>

/*
    Purpose: Create a program setbits(x, p, n, y) that returns x with the n bits that begin at position p set to the rightmost n bits of y 
*/

unsigned setbits(unsigned x, int p, int n, unsigned y);
unsigned getbits(unsigned x, int p, int n);

int main() {
    unsigned x = 75;
    unsigned y = 110; 
    printf("%u\n", setbits(x, 4, 2, y));
}

unsigned setbits(unsigned x, int p, int n, unsigned y) {
    unsigned rightmost_bits_y = getbits(y, n-1, n);
    // Now we have the rightmost
    // Left shift until they match the position of p
    rightmost_bits_y = rightmost_bits_y << (p - n + 1);
    // Now they are aligned
    unsigned cleared_out_x = x & ~(((1 << n) - 1) << (p - n + 1));

    return cleared_out_x | rightmost_bits_y;

    // Now we want to clear the bits that are in range [p, p+n] inclusive for x
    // Make a bit string of 1s, then left shift for the number of places we want to make 0
    // Leftshift until it's aligned, and fill those with 1s    
}

/*
    How does this work?
    - The left parentheses expression cuts off the numbers on the right of the range of getbits
    - The right parentheses expression adds 0s to all the numbers outside of the range of getbits
    and 1s to the inside, then &'s them, so only the numbers in the range are grabbed
    - In other words, the right expression makes an int of all 1s, then shifts n positions, but then uses the one's complement to make all the 1s->0s and all the 0s->1s to have bits with 1s only in the range of getbits 
*/
unsigned getbits(unsigned x, int p, int n) {
    return (x >> (p + 1 - n)) & ~(~0 << n); 
}
