#include <stdio.h>

/*
    Purpose: Write a function rightrot(x, n) that returns the value of the integer x rotated to the riget by n positions.
*/

unsigned rightrot(unsigned x, int n);
unsigned getbits(unsigned x, int p, int n);

int main() {
    unsigned x = 22;
    printf("Size of unsigned: %d\n", sizeof(unsigned));
    printf("%u\n", rightrot(x, 2));
}

unsigned rightrot(unsigned x, int n) {
    // Get the bits that are going to be rotated out
    // We are not going to account for the edge case where n is equal to or of size unsigned
    unsigned bits_to_rotate = getbits(x, n-1, n);
    x = x >> n;
    // Shift these bits to the end
    int end_of_bits = sizeof(unsigned) * 8 - 1;
    // Now we must shift the bits_to_rotate to the end
    // n long and the range is [0, end_of_bits] inclusive which is end_of_bits+1 number of elements
    bits_to_rotate = bits_to_rotate << (end_of_bits + 1 - n);
    // Create a mask for the last n bits of x
    // x = (x & ~((1 << n) - 1)) << (end_of_bits + 1 - n);
    
    return bits_to_rotate | x;
}

unsigned getbits(unsigned x, int p, int n) {
    // We have the original x = 10010
    // We want the first two bits starting at position 2, so it's getbits(x, 2, 2)
    // This means that we have to create a mask that is 00110
    // what is this mask flipped? 11001
    // How can we construct this? Start with an unsigned int 1, then shift left n times and - 1
    // This will give you a trail of 1s that are of size n, then you can shift p-n+1 times
    return (x >> (p+1-n)) & ~(~0 << n);
}
