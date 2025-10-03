#include <stdio.h>
#include <ctype.h>

/*
    Purpose: Write a function expand(s1, s2) that expands shorthand notations like a-z in the string s1 into the equivalent complete list abc...xyz in s2.
*/

void expand(char s1[], char s2[]);

int main() {
    char s1[100];
    char s2[100];
    
    char *tests[] = {"a-z", "A-Z", "0-9", "a-b-c", "-a-z", "a-z-", "z-a", "f-z"};
    int numTests = sizeof(tests) / sizeof(tests[0]);

    for (int t = 0; t < numTests; t++) {
        expand(tests[t], s2);
        printf("%s -> %s\n", tests[t], s2);
    }
    
    return 0;
}

void expand(char s1[], char s2[]) {
    /*  Algorithm:
            Wait till we find a '-' because then we can grab the element on the left
            and right
    */ 
    int i = 0, j = 0;
    
    while (s1[i] != '\0') {
        if (s1[i] == '-' && i > 0 && s1[i+1] != '\0') {
            char left = s1[i-1];
            char right = s1[i+1];

            if ((isdigit(left) && isdigit(right) && left < right) ||
                (islower(left) && islower(right) && left < right) ||
                (isupper(left) && isupper(right) && left < right)) {
                // How are we going to print everything in between and including these
                // two elements
                    for (char c = left; c <= right; c++) {
                        s2[j++] = c;
                    }
                    s2[j] = '\0';
            } 
        }
        i++;
    } 
}
