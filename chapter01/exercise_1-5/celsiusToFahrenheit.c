#include <stdio.h>

void main() {
    float fahr, celsius;

    printf("----Celsius to Fahrenheit Conversion Table----\n");

    for(celsius = 0; celsius < 300; celsius += 20) {
        fahr = celsius * (9.0 / 5.0) + 32;
        printf("%3.0f %6.1f\n", celsius, fahr);
    } 
}
