#include <stdio.h>
#include <string.h>

/*
    Purpose: Rewrite readlines to store lines in an array supplied by main, rather than calling alloc to maintain storage
*/

// The difference between this readlines and the readlines provided
// We are not going to use allocate anymore
// We will read all the lines into a large character buffer to avoid having to allocate every time
// There is no more maxlines, there is only maxchars
// lineptr is not a pointer to a string for each spot in the array, instead we are using indices from the 

// Some outside storage that we should be aware of:
char lines[MAXCHARS];
char *lineptr[MAXLINES];
int curr_pos = 0;

int readlines(int *lineptr[], int maxlines, int maxchars) {
    int len, nlines;
    int p;
    char line[MAXLEN]; // Can not just straight read getline into the lines[curr_pos] because that is a single spot and not passing an array
    
    nlines = 0;
    
    while((len = getline(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || curr_pos + len > maxchars){
            return -1;
        }
        else {
            line[len-1] = '\0';
            strcpy(&lines[curr_pos], line);
            lineptr[nlines++] = &lines[curr_pos];
            curr_pos += len;
        }
    }
    return nlines;
}
