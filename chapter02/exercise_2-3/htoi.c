# include <stdio.h>

/*
    Purpose: Create a program that converts hexadecimal digits to integer values
*/

int hex_to_dec(char hex[]);

int main() {

    printf("%d\n", hex_to_dec("1AB9F"));
}

int hex_to_dec(char hex[]) {
    int running_sum = 0;
    int i = 0;
    // We want to read
    while (hex[i] != '\0' && i >= 0 && ((hex[i] >= '0' && hex[i] <= '9') || (hex[i] >= 'a' && hex[i] <= 'f') || (hex[i] >= 'A' && hex[i] <= 'F'))) {
        int converted_int;
        if (hex[i] >= '0' && hex[i] <= '9') {
            converted_int = hex[i] - '0';
        } 
        else if (hex[i] >= 'a' && hex[i] <= 'f') {
            converted_int = (hex[i] - 'a') + 10;
        }
        else if (hex[i] >= 'A' && hex[i] <= 'F') {
            converted_int = (hex[i] - 'A') + 10;
        }
        running_sum = converted_int + 16 * running_sum;
        i++;
    }
    return running_sum;
}
