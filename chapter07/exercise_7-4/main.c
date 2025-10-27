/*
    Purpose: Write a private version of scanf analogous to minprintf from the previous section
*/

#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

int my_scanf(char *format, ...);

int main() {
    int d;
    char s[20];
    float f;
    if (my_scanf("Hi %s %d %f", s, &d, &f)) {
        printf("s: %s\nd: %d\nf: %f\n", s, d, f);
        return 0;
    }
    printf("\nBroken\n");
    return 1;
}

int my_scanf(char *format, ...) {
    char *fp;
    va_list ap;
    va_start(ap, format);
    int c;
    for (fp = format; *fp; fp++) {
        if (isspace(*fp)) {
            while (isspace(c = getchar()))
                ;
            ungetc(c, stdin);
            continue;
        }
        else if (*fp != '%') {
            c = getchar();
            if (c != *fp) return 0;
            continue;
        } 
        switch(*(++fp)) {
            case 'd':
                // Read digit
                // How do you read a digit from a string and convert it to an actual digit?
                while (isspace(c = getchar()))
                    ;
                int sign = 1;
                int digit = 0;
                if (c == '-') {
                    sign = -1;
                    c = getchar();
                }
                if (!isdigit(c)) return 0;
                do {
                    digit = digit * 10 + (c - '0');
                } while (isdigit(c = getchar()));
                ungetc(c, stdin); 
                int *format_d = va_arg(ap, int *);
                *format_d = digit; // Store our value into the val
                break;
            case 's':
                scanf("%s", va_arg(ap, char *));
                break;
            case 'f':
                scanf("%f", va_arg(ap, float *));
                break;
        }
    } 
    va_end(ap);
    return 1;
}
