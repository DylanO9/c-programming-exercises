#include <stdio.h>
#include <string.h>
#define MAX_CHARS 100

/*
    Purpose: Write a program to compare two files, printing the first line where they differ.
*/


int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "There are not enough files to compare\n");
        return 1;
    }
    
    char line_1[MAX_CHARS];
    char line_2[MAX_CHARS];
    FILE *file_1;
    FILE *file_2;

    if ((file_1 = fopen(*(argv + 1), "r")) == NULL) {
        fprintf(stderr, "There was a problem opening the first file\n");
        return 1;
    }
    if ((file_2 = fopen(*(argv + 2), "r")) == NULL) {
        fprintf(stderr, "There was a problem opening the second file\n");
        return 1;
    }

    while (fgets(line_1, MAX_CHARS, file_1) != NULL && fgets(line_2, MAX_CHARS, file_2) != NULL) {
        if (strcmp(line_1, line_2) != 0) {
            printf("Line 1: %s\n", line_1);
            printf("Line 2: %s\n", line_2);
            fclose(file_1);
            fclose(file_2);
            return 0;
        }
    }

    fclose(file_1);
    fclose(file_2);
    fprintf(stderr, "One of the files reached the end before two different lines were found\n");
    return 0; 
}
