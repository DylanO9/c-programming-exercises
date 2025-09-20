#include <stdio.h>

/*  Purpose:
    Read the characters in until a new line or EOF, but do not use the && or || operators
*/

int main() {
    int i = 0;
    int c; 
    int lim = 10;
    char s[lim];
    while (i < lim-1) {
        c = getchar();
        if (c == '\n') {
            break;
        } else if (c == EOF) {
             break;
        }
        s[i] = c;
        i++;
    }
    s[i] = '\0';
    printf("Result: %s\n", s); // Reads the array until the null character
}
