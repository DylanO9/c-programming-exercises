#include <stdio.h>
#include <string.h>

#define MAX_BUFFER 11

int main() {
                            

    char buffer[MAX_BUFFER] = {0};     int c;
    int len_buffer = 0;    

    while ((c = getchar()) != EOF) {
                if (c == '\n') {
                        for (int i = 0; i < len_buffer; i++) {
                putchar(buffer[i]);
            }
            putchar('\n');
            memset(buffer, 0, sizeof(buffer));
            len_buffer = 0;
            continue;
        }     
    

                if (len_buffer < MAX_BUFFER - 1) {
                        buffer[len_buffer] = c;
            buffer[len_buffer+1] = '\0';             len_buffer++;
        } 
        
                if (len_buffer == MAX_BUFFER - 1) { 
            int last_blank = -1;
            for (int i = 0; i < MAX_BUFFER; i++) {
                if (buffer[i] == '\t' || buffer[i] == '') {
                    last_blank = i;    
                }
            }
            
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
