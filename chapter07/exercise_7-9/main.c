/*
    Purpose: Functions like usupper can be implemented to save space or to save time
*/

#include <stdio.h>

int my_isupper(int);

int main () {
    printf("Test: %c\n", my_isupper('a'));
}

int my_isupper(int c) {
    if (c >= 'A' && c <= 'Z') {
        return 1;
    }
    return 0;
}

int save_space(int c) {
    // Less space
    return (c >= 'A' && c <= 'Z');
}

#define YES     1
#define NO      0

static char upper_table[256];

void init_upper_table(void) {
    for (int i = 0; i < 256; ++i)
        upper_table[i] = (i >= 'A' && i <= 'Z') ? YES : NO;    
}

int save_time(int c) {
    // Less time
    return upper_table[(unsigned char)c];     
}

