/*
    Purpose: Write a program that will print arbitrary input in a sensible way. As a minimum, it should print non-graphic characters in octal or hexadecimal according to local custom, and break long text lines.
*/

#include <stdio.h>
#include <ctype.h>

#define MAXLINE 10

int main () {
    int c;
    FILE *file;
    const char *filename = "test.txt";
    file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Error opening file");
        return 1;    
    }   

    fprintf(file, "This is a long form of input\n");
    fputc(127, file);
    fprintf(file, "\nHere is another long line: %c", 31);
    fclose(file);

    file = fopen(filename, "rb"); // Open in binary read mode
    if (file == NULL) {
        perror("Error opening file for reading");
        return 1;
    }

    int counter = 0;
    while ((c = fgetc(file)) != EOF) {
        if (isprint(c)) {
            putchar(c);
        } else {
            printf("\\%o", (unsigned char) c);
        }
        
        counter++;
        if (counter >= MAXLINE) {
            putchar('\n');
            counter = 0;
        }
    }      
    printf("\n");
    fclose(file);
}
