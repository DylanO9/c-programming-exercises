/*
    Purpose: Write a program to print a set of files, starting each new one on a new page, with a title and a running page count for each file
*/
#include <stdio.h>


void print_file(FILE *fp, const char *filename, int *page_count);

int main(int argc, char *argv[]) {
    FILE *fp;
    int page_count = 0;
    
    if (argc == 1) {
        fprintf(stderr, "Not enough files\n");
        return 1;
    }
    while (--argc > 0) {
        if ((fp = fopen(*++argv, "r")) == NULL) {
            fprintf(stderr, "Can't open file: %s\n", *argv);
            continue; 
        } else {
            print_file(fp, *argv, &page_count);
            fclose(fp);
        }
    }
    return 0;
}

void print_file(FILE *fp, const char *filename, int *page_count) {
    int c;
    int num_lines = 0;

    printf("\fTitle: %s\tPage: %d\n\n", filename, ++(*page_count));

    while ((c = getc(fp)) != EOF) {
        putchar(c);
        if (c == '\n') {
            num_lines++;
            if (num_lines == 60) {  // new page every 60 lines
                printf("\fTitle: %s\tPage: %d\n\n", filename, ++(*page_count));
                num_lines = 0;
            }
        }
    }
}
