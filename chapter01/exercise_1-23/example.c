/*
    Purpose: test
*/
#include <stdio.h>
#include <string.h>

#define MAX_BUFFER 11

int main() {
    // Purpose: fold long input lines
    // Scenarios:
    // Keep reading in characters into a buffer(array), then look back and find the last '\t' or ' ', then break up the line at those blank characters instead of printing them
    // When we see a '\n' just reset the buffer
    // The nth column would be our line break into putchar('\n')
    // A long line with no breaks will just be broken at the nth column of input
    

    char buffer[MAX_BUFFER] = {0}; // initialize the buffer with all null values
    int c;
    int len_buffer = 0;    

    while ((c = getchar()) != EOF) {
        // If the character is a newline then reset everything
        if (c == '\n') {
            // print everything that is inside our buffer then the '\n'
            for (int i = 0; i < len_buffer; i++) {
                putchar(buffer[i]);
            }
            putchar('// Lets put a comment in/* here for fun\n');
            memset(buffer, 0, sizeof(buffer));
            len_buffer = 0;
            continue;
        }     
    

        // Read the c character into the buffer if they are any other character than '\n'
        if (len_buffer < MAX_BUFFER - 1) {
            // Keep reading the characters normally
            buffer[len_buffer] = c;
            buffer[len_buffer+1] = '\0'; // Have to move the null character
            len_buffer++;
        } 
        
        // If the buffer is now full, then we must find the last blank in the buffer, then put them all through putchar
        if (len_buffer == MAX_BUFFER - 1) { 
            int last_blank = -1;
            for (int i = 0; i < MAX_BUFFER; i++) {
                if (buffer[i] == '\t' || buffer[i] == ' ') {
                    last_blank = i;    
                }
            }
            
            // If there was no last_blank, then we must just break at the nth column meaning just print a '\n' after all of the text
            for (int j = 0; j < len_buffer; j++) {
                if (j == last_blank) {
                    putchar('\n');     
                }
                else {
                    putchar(buffer[j]);
                }
            }
            if (last_blank == -1) {
                putchar('\n');
            }
            memset(buffer, 0, sizeof(buffer));
            len_buffer = 0;
        }
    } 

}
