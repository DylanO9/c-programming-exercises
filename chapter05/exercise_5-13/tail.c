#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
    Purpose: Write the program tail, which prints the last n lines of its input
    Outline:
        - Process the argument
*/

#define DEFAULT_NUMBER_OF_LINES             10
#define MAX_CHARS                           10000
#define MAX_LINES                           100
#define MAX_CHARS_PER_LINE                  100

int my_getline(char *);

int main(int argc, char *argv[]) {
    char line[MAX_CHARS_PER_LINE]; 
    char *lines[MAX_LINES];
    char storage[MAX_CHARS];
    char *sp = storage;
    int storage_index = 0;
    int length;
    int last_n_lines = argc != 1 ? atoi(*(argv + 1)) : DEFAULT_NUMBER_OF_LINES;
    int line_index;
    
    printf("last_n_lines: %d\n", last_n_lines);
    while((length = my_getline(line)) > 0) {
        if (line_index >= MAX_LINES) {
            printf("Too many lines\n");
            return 1;
        }        

        if (length + storage_index + 1 < MAX_CHARS) {
            strcpy(sp, line);
            lines[line_index++] = sp;
            storage_index += length + 1;
            sp += length + 1;
        } else {
            printf("Not enough space to hold all lines\n");
            return 1;
        }
    }
    if (last_n_lines < 0 || line_index - last_n_lines < 0) {
        printf("Not enough lines for %d lines to be printed\n", last_n_lines);
        return 1;
    } 

    int start = line_index > last_n_lines ? line_index - last_n_lines : 0;
    for (int i = start; i < line_index; i++) {
        printf("%s", lines[i]);
    }
    return 0;
}

int my_getline(char *line) {
    int c, i = 0;
    
    while ((c = getchar()) != EOF && c != '\n') {
        if (i < MAX_CHARS_PER_LINE - 1)
            line[i++] = c;
    }
    
    if (c == '\n' && i < MAX_CHARS_PER_LINE - 1) {
        line[i++] = '\n';    
    }
    line[i] = '\0';
    return i;
}
