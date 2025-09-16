#include <stdio.h>

#define TAB_STOP 8

int main() {
        int c;
        int pos = 0;
        while ((c = getchar()) != EOF) {
            if (c == '\n') {
                pos = 0;
                putchar('\n');
            } else if (c == '\t') {
                int num_of_spaces = TAB_STOP - (pos % TAB_STOP);
                for (int i = 0; i < num_of_spaces; i++) {
                    putchar(' ');
                    pos++;
                }
            } else {
                putchar(c);
                pos++;
            }
        }
    return 0;
}
