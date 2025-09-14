#include <stdio.h>
#include <string.h>

#define MAX_LIMIT 100

int my_getline(char s[], int limit);
void copy(char target[], char source[]);

int main() {
	char line[MAX_LIMIT];
	char longest_line[MAX_LIMIT];
	int longest_length = 0;
	int length;
	// The length that is returned is the length of characters including the newline character, but without the null character
	// printf("%d", my_getline(line, MAX_LIMIT));
	/*
		strncpy(line, "longest", sizeof(line) - 1);
		copy(longest, line);
		printf("%s", longest);	
	*/

	// Looks like both of my functions work with these tests
	while ((length = my_getline(line, MAX_LIMIT)) > 0) {
		if (length > longest_length) {
			longest_length = length;
			copy(longest_line, line);
		} 
	}

	if (longest_length > 0) {
		printf("%s", longest_line);
	}

	return 0;
}

int my_getline(char s[], int limit) {
	/* 
		Strategy:
		Use c to store the current character and place it within s[i] until we find a newline character
		which we will then place it at this index
 		and add a null character to the end of the array to make sure we have this determinant
	*/
	int c, i;
	for (i = 0; (c = getchar()) != EOF && i < limit - 1 && c != '\n'; i++) {
		s[i] = c;
	}	
	// if it exited because of a newline character, then we must check this. Do we have to check that s has one more spot to place '\n'
	if (c == '\n') {
		// Place this newline into the array
		s[i] = c;	
		i++;
	}	
	
	// We need to place a null character at the end as well
	s[i] = '\0';

	return i;
}

void copy(char target[], char source[]) {
	/*
		Strategy:
		Assume that the target can hold the source
		because in our function we will only allow for it to get to this portion if this check is made
	*/
	
	int i = 0;
	while (source[i] != '\0') {
		target[i] = source[i];
		i++;	
	}
	
	// By the end of our while loop, we will be at a null character. We want to place a new null
	target[i] = '\0';
	
	return;
}
