/*
    Purpose: Revise minprintf to handle more of the other facilities of printf
*/

#include <stdarg.h>
#include <stdio.h>
void minprintf(char *, ...);

int main() {
    minprintf("%count:%u\n", 'C', 10u);
    return 0;    
}

/* minprintf: minimal printf with variable argument list */
void minprintf(char *fmt, ...)
{
    va_list ap; /* points to each unnamed arg in turn */
    char *p, *sval;
    
    int ival;
    double dval;
    unsigned int uival;
    va_start(ap, fmt); /* make ap point to 1st unnamed arg */
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }
        switch (*++p) {
            case 'i':
            case 'd':
                ival = va_arg(ap, int);
                printf("%d", ival);
                break;
            case 'f':
                dval = va_arg(ap, double);
                printf("%f", dval);
                break;
            case 's':
                for (sval = va_arg(ap, char *); *sval; sval++)
                putchar(*sval);
                break;
            case 'c':
                ival = va_arg(ap, int); 
                printf("%c", ival);
                break;
            case 'u':
                uival = va_arg(ap, unsigned int);
                printf("%u", uival);
                break; 
            default:
                putchar(*p);
                break;
        }
    }
    va_end(ap); /* clean up when done */
}
