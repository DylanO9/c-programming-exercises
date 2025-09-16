#include <stdio.h>

#define TAB_STOP 8

int main() {
    int c;
    int pos = 0;

    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            int start = pos;
            int num_of_tabs = 0;
            pos++;
            if (pos % TAB_STOP == 0) {
                num_of_tabs++;
            }
            int whitespace_count = 1;
            while ((c = getchar()) == ' ') {
                if (pos % TAB_STOP == 0) {
                    num_of_tabs++;
                }
                whitespace_count++;
                pos++;
            }
            int closest_tab_pos = (pos / TAB_STOP) * TAB_STOP;
            int closest = start > closest_tab_pos ? start : closest_tab_pos;
            int num_of_spaces = pos % closest;
            for (int i = 0; i < num_of_tabs; i++) {
                putchar('\t');
            }
            for (int j = 0; j < num_of_spaces; j++) {
                putchar(' ');
            }
            
            if (c == EOF) {
                break;
            }
        } 

        if (c == '\n') {
            pos = 0;
            putchar(c);
        } else {
            putchar(c);
            pos++;
        } 
    } 

    return 0;
}
