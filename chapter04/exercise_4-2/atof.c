#include <stdio.h>

/*
    Purpose: Extend atof to handle scientific notation of the form 123.45e-6 where a floating-point number may be followed by e or E and an optionally signed exponent
*/

double atof(char s[]);

int main() {
    char s[100] = "123.45e6";

    printf("Original string: %s\n", s);
    printf("%f\n", atof(s));     
}

double atof(char s[]) {
    double result = 0;
    int i;
    for (i = 0; s[i] != '\0' && s[i] != '.'; i++) {
        result = result * 10 + (s[i] - '0'); // Here we are taking the current result we have, moving all the numbers one space to the left, and then adding the current number into the rightmost spot
    } 

    if (s[i] == '\0') {
        return result; // We can return result here because there are no decimal places to move    
    }
    
    
    // If we can keep going that means that we are at a .
    i++;
    int division_count = 0;
    for (;s[i] != '\0' && s[i] != 'e' && s[i] != 'E'; i++, division_count++) {
        result = result * 10 + (s[i] - '0');
    }

    // We have a current division_count
    if (s[i] == '\0') {
        for (int j = 0; j < division_count; j++) {
            result /= 10;
        } 
        return result;
    }  

    // If we did not land on a null character, then we can move one spot over
    i++;
    bool negative = false;
    // Now we can see if there is a negative sign
    if (s[i] == '-') {
        negative = true;
        i++;
    }
    
    // Now we want to read in whatever numbers are after the sign so it could be one digit to many digits
    int exponent = 0;
    for (; s[i] != '\0'; i++) {
        exponent = exponent * 10 + (s[i] - '0');
    }
    if (negative) exponent *= -1;    
    // Now we have finished reading the exponent in, and we have a variable that holds it
    // Our division_count means how many times we divide 10, our exponent if negative will add to it and if positive will do the opposite
    if (exponent < 0) {
        division_count += (-1 * exponent);
    } else {
        division_count -= exponent;
    }

    // Now we could either be going forwards or backwards
    if (division_count > 0) {
        for (int j = 0; j < division_count; j++) {
            result /= 10;
        }   
    } else {
        division_count *= -1;
        for (int j = 0; j < division_count; j++) {
            result *= 10;
        }
    }
    return result;
}
