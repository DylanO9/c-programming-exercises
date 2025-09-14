#include <stdio.h>

int main () {
	char c;
	
	while ((c = getchar()) != EOF) {
		if (c == ' ') {
			putchar(c);
			while (c == ' ') {
				c = getchar();
			}
			if (c != EOF) {
				putchar(c);
			}
		} else {
			putchar(c);
		}
	}
	printf("\n");
}
		
