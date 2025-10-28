/*
    Purpose: Rewrite the program cat from Chapter 7 using read, write, open, and close instead of their standard library equivalents
*/
#include <stdio.h>
#include <stdarg.h>
#include <fcntl.h>
#include <unistd.h>

int print_file(char *);

int main(int argc, char *argv[]) {
    if (argc == 1) {
        fprintf(stderr, "There are not enough files\n");    
        return 1;
    } 
    
    while (--argc > 0) {
        print_file(*++argv);        
    } 
    return 0;
}

int print_file(char *file_name) {
    int n, fd;
    char buf;

    if ((fd = open(file_name, O_RDONLY, 0)) == -1) {
        fprintf(stderr, "There was a problem opening the file: %s\n", file_name); 
        return 0;
    }

    int chars_written;
    while ((n = read(fd, &buf, 1)) == 1) {
        chars_written = write(STDOUT_FILENO, &buf, n);

        if (chars_written < n) {
            fprintf(stderr, "Some problem writing for file: %s", file_name);
            return 0;
        }
    }

    if (close(fd) == -1) { 
        fprintf(stderr, "Failure to close file: %s\n", file_name);
        return 0;
    }
    return 1;
}
