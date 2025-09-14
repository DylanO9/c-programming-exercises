#include <stdio.h>

int main() {
	char c;
	int count = 0;
	while((c = getchar()) != EOF) {
		if (c == '\t' || c == '\n' || c == ' ') {
			count++;
		}
	}
	printf("%d", count);
	return 0;
}
