#include <stdio.h>

/*
    Purpose: Define a macro swap(t, x, y) that interchanges two arguments of type t to practice defining macros that include functions and understand how they swap the defined name with replacement text
*/

#define swap(t, x, y)   t temp = x; x = y; y = temp;

int main() {
    int x = 0;
    int y = 10;
    swap(int, x, y);
    printf("x=%d\ny=%d\n", x, y);
    return 0;
}
