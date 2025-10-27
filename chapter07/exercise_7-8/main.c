/*
    Purpose: Write a program to print a set of files, starting each new one on a new page, with a title and a running page count for each file
*/
#include <stdio.h>


int print_file(FILE *fp);

int main(int argc, char *argv[]) {
    FILE *fp;
    int page_count = 0;
    
    if (argc == 1) {
        fprintf(stderr, "Not enough files\n");
    }
    while (--argc > 0) {
        page_count++;
        if ((fp = fopen(*++argv, "r")) == NULL) {
            fprintf(stderr, "Can't open file: %s\n", *argv);
        } else {
            printf("---------------------\n");
            printf("Title: %s\tCount: %d\n", *argv, page_count);
            print_file(fp);
            fclose(fp);
        }
    }
    return 0;
}

int print_file(FILE *fp) {
    int c;
    while ((c = getc(fp)) != EOF) {
        putchar(c);    
    } 
    return 1;
}
