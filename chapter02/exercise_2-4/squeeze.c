#include <stdio.h>

/*
    Purpose: Create a program that is an alternative version of squeeze(s1, s2) that deletes
    each character in s1 that matches any character in the string s2
*/

void squeeze(char s1[], char s2[]);

int main() {
    char s1[20] = {'d', 'd', 'd', 'y', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'l', 'a', 'n', '\0'};
    char s2[20] = {'d', 'n', '\0'};
    printf("Original String: %s\n", s1);
    printf("Remove these characters: %s\n", s2);
    squeeze(s1, s2);
    printf("After Squeeze: %s\n", s1); 
    
    // Edge case
    char s3[20] = {'d', 'd', 'd', 'y', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'l', 'a', 'n', '\0'};
    char s4[20] = {'\0'};
    printf("Original String: %s\n", s3);
    printf("Remove these characters: %s\n", s4);
    squeeze(s3, s4);
    printf("After Squeeze: %s\n", s3); 
}

void squeeze(char s1[], char s2[]) {
    int slow = 0;
    int fast = 0;
    while (s1[fast] != '\0') {
        bool found = false;
        for (int i = 0; s2[i] != '\0'; i++) {
            if (s1[fast] == s2[i]) {
                found = true;
                break;
            }
        }

        // We want to remove each character in s1 that matches a character from s2
        // So when a character is not found, then we place the character into the slow slot and move
        // to the next
        // If it is found, then we should ignore it and move to the next
        if (!found) {
            s1[slow++] = s1[fast++];
        }
        else {
            fast++;
        }
    }
    // Fast ends on '\0', but that doesn't mean slow does.
    // We want to make sure slow has a '\0' character at the end
    s1[slow] = '\0';   
}
