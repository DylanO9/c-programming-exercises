#include <stdio.h>
#define IN	1	/* inside a word */
#define OUT	0	/* outside a word */
int main() {
	int c, state = OUT;
	int firstWord = 1;
	while ((c = getchar()) != EOF) {
		if (c == ' ' || c == '\n' || c == '\t') 
			state = OUT;
		else if (state == OUT) {
			state = IN;
			putchar('\n');
		}
		putchar(c);
	}
	return 0;
}	
