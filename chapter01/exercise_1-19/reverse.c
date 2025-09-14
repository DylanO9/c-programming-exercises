#include <stdio.h>
#include <string.h>

#define MAX_LIMIT 100

int my_getline(char s[], int limit);

int main() {
	char line[MAX_LIMIT];
	int length;

	while ((length = my_getline(line, MAX_LIMIT)) > 0) {
		int i = length - 1;
		while (i >= 0 && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')) {
			i--;
		}
		
		if (i >= 0) {
			line[i + 1] = '\n';
			line[i + 2] = '\0';
		}
		
		// Reverse
		int left = 0;
		int right = i;
		while (left < right) {
			char temp = line[left];
			line[left] = line[right];
			line[right] = temp;
			left += 1;
			right -= 1;
		}
		printf("%s", line);
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


