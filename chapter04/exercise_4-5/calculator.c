#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAXOP   100
#define NUMBER  '0'

int getop(char []);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);
void printTop(void);
void duplicateTop(void);
void swapTopTwo(void);
void clearStack(void);

int main() {
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
        switch (type) {
        case NUMBER:
            push(atof(s));
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '/':
            op2 = pop();
            if (op2 != 0.0)
                push(pop() / op2);
            else
                printf("error: zero divisor\n");
            break;
        case '%':
            op2 = pop();
            if (op2 != 0.0) {
                int remainder = (int)pop() % (int)op2;
                if (remainder < 0)
                    remainder += (int)op2;
                push(remainder);
            }
            else
                printf("error: trying to divide by 0 for modulus\n");
            break;
        case 'e':
            push(exp(pop()));
            break;
        case 'w':
            push(sin(pop()));
            break;
        case 'r':
            op2 = pop();
            push(pow(pop(), op2));
            break;
        //case 'p':
            //printTop();
            //break;
        case 'd':
            duplicateTop();
            break;
        case 's':
            swapTopTwo();
            break;
        case 'c':
            clearStack();   
            break; 
        case '\n':
            printTop();
            // printf("\t%.8g\n", pop());
            break;  
        default:
            printf("error: unknown command %s\n", s);
            break;
        }
    }
    return 0;
}

#define MAXVAL  100
int sp = 0;
double val[MAXVAL];

void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

double pop(void) {
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

void printTop(void) {
    if (sp > 0)
        printf("%f\n", val[sp-1]);
    else
        printf("error: there is no top of the stack\n");
}

void duplicateTop(void) {
    if (sp > 0)
        push(val[sp-1]);
    else
        printf("error: there are no elements in the stack\n");
}

void swapTopTwo(void) {
    if (sp > 1) {
        // Pop the top two elements
        double second_element = pop();
        double first_element = pop();
        push(second_element);
        push(first_element);
    } else {
        printf("error: there are not enough elements in the stack\n");
    } 
}

void clearStack(void) {
    sp = 0;        
}

int getop(char s[]) {
    int i, c;
    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    if (!isdigit(c) && c != '.')
        return c;
    i = 0;
    if (isdigit(c))
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.')
        while (isdigit(s[++i] = c = getch()))
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
