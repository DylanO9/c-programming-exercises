#include <stdio.h>

int main() {
	char c = 'A';
	int i = 'A';
	printf("Character constant: %c\n", c);
	printf("As integer (ASCII value: %d\n", c);
	printf("Stored in int directly: %d\n", i);
	printf("'B' as integer: %d\n", 'B');
	printf("'a' as integer: %d\n", 'a');
	
	printf("Difference between 'a' and 'A': %d\n", 'a' - 'A');
	return 0;
}
