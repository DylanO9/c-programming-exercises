#include <stdio.h>
#include <stdlib.h>

#define TAB_STOP_DEFAULT 8

int main(int argc, char *argv[]) {
        int TAB_STOP = argc != 1 ? atoi(*(argv + 1)) : TAB_STOP_DEFAULT; 
        printf("Tab stops: %d\n", TAB_STOP);
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
