#include <stdio.h>

double convertToCelsius(double fahrenheit);

int main() {
	printf("---Convert to Celsius Table---\n");
	for (int i = 0; i <= 300; i = i + 20) {
		printf("%d\t%.2f\n", i, convertToCelsius(i));
	}
	return 0;
}

double convertToCelsius(double fahrenheit) {
	return (5.0 / 9.0) * (fahrenheit - 32.0);	
}
