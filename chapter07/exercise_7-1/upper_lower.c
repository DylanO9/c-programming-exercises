#include <stdio.h>
#include <string.h>
#include <ctype.h>

/*
    Purpose: Write a program that converts upper case to lower or lower case to upper, depending on the name it is invoked with, as found in argv[0]
*/

int main(int argc, char *argv[]) {
    if (strcmp(*argv, "./lower") == 0) {
        int c;
        while ((c = getchar()) != EOF) {
            putchar(tolower(c));
        }
    }
    else if (strcmp(*argv, "./upper") == 0) {
        int c;
        while ((c = getchar()) != EOF) {
            putchar(toupper(c));
        } 
    }
}
