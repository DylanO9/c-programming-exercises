#include <ctype.h>
#include <stdio.h>

/*
    Purpose: As written, getint treats a + or - not followed by a digit as a valid representaiton of zero. Fix it to push such a character back into input
*/ 

#define SIZE 100

int getch(void);
void ungetch(int);

int main()
{
    int n, array[SIZE], getint(int *), output;
    for (n = 0; n < SIZE && (output = getint(&array[n])) != EOF;) {
        if (output != 0)
            n++;
    } 
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);   
    }
    printf("\n");
    return 0;
}

/* getint: get next integer from input into *pn */
int getint(int *pn)
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
