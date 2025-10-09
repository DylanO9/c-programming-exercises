#include <ctype.h>
#include <stdio.h>

/*
    Purpose: Write getfloat, the floating-point analog of getint 
*/

#define SIZE 100

int getch(void);
void ungetch(int);

int main()
{
    int n, getfloat(float *), output;
    float array[SIZE];
    for (n = 0; n < SIZE && (output = getfloat(&array[n])) != EOF;) {
        if (output != 0)
            n++;
    }
    for (int i = 0; i < n; i++) {
        printf("%f ", array[i]);
    }
    printf("\n");
    return 0;
}

/* getint: get next integer from input into *pn */
int getfloat(float *pn)
{
    int c, sign;
    while (isspace(c = getch()))
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        int temp = c;
        c = getch();
        if (!isdigit(c)) {
            ungetch(temp);
            ungetch(c);
            return 0;
        }
    }
    for (*pn = 0; c != EOF && isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    
    // Handle decimals
    int decimal_places = 0;
    if (c == '.') {
        c = getch();
        for (*pn; c != EOF && isdigit(c); c = getch()) {
            decimal_places++;
            *pn = *pn * 10 +  (c - '0');
        }
        for (decimal_places; decimal_places > 0; decimal_places--) {
            *pn = *pn / 10;
        }
    }    


    *pn *= sign;
    if (c != EOF)
        ungetch(c);
    return c;
}

#define BUFSIZE 100

char buf[BUFSIZE];  // buffer for ungetch
int bufp = 0;       // next free position in buf

int getch(void)  // get a (possibly pushed-back) character
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)  // push character back on input
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
