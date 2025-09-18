#include <stdio.h>
#include <limits.h>

// Purpose: Determine the ranges of char, short, int, and long variables, unsigned and signed, by printing appropriate values from standard headers and by direct computation.

#include <stdio.h>

int main(void) {
    int bits;

    // char
    bits = sizeof(char) * 8;
    printf("char:\n");
    printf("  signed   [%d, %d]\n",
           -(1 << (bits - 1)),
           (1 << (bits - 1)) - 1);
    printf("  unsigned [0, %u]\n",
           (1U << bits) - 1);

    // short
    bits = sizeof(short) * 8;
    printf("short:\n");
    printf("  signed   [%d, %d]\n",
           -(1 << (bits - 1)),
           (1 << (bits - 1)) - 1);
    printf("  unsigned [0, %u]\n",
           (1U << bits) - 1);

    // int
    bits = sizeof(int) * 8;
    printf("int:\n");
    printf("  signed   [%d, %d]\n",
           -(1 << (bits - 1)),
           (1 << (bits - 1)) - 1);
    printf("  unsigned [0, %u]\n",
           (1U << (bits - 1)) * 2U - 1); // The reason this doesn't work is because before you - 1 we are out of range

    // long
    bits = sizeof(long) * 8;
    printf("long:\n");
    printf("  signed   [%ld, %ld]\n",
           -(1L << (bits - 1)),
           (1L << (bits - 1)) - 1);
    printf("  unsigned [0, %lu]\n",
           ((1UL << (bits - 1)) * 2UL) - 1);
    
    printf("---limits.h---\n");
    printf("char:\n");
    printf("  signed  [%d, %d]\n",
            SCHAR_MIN, SCHAR_MAX);
    printf("  unsigned [0, %u]\n",
            UCHAR_MAX);
    printf("short:  [%d, %d]\n", SHRT_MIN, SHRT_MAX);
    printf("ushort: [0, %u]\n", USHRT_MAX);
    printf("int:    [%d, %d]\n", INT_MIN, INT_MAX);
    printf("uint:   [0, %u]\n", UINT_MAX);
    printf("long:   [%ld, %ld]\n", LONG_MIN, LONG_MAX);
    printf("ulong:  [0, %lu]\n", ULONG_MAX);
    return 0;
}

