#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>    // For the bool type

#define MAXOP   100     // Max size of operand or operator
#define NUMBER  '0'     // Signal that a number was found
#define MAXVAL  100

/* ------ Function Declarations ------ */
int getop(char []);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);
void printTop(void);
void duplicateTop(void);
void swapTopTwo(void);
void clearStack(void);

/* ------ Global Variables ------ */
double variables[26];
int last_var = -1;
double last_print = 0.0;
char s[MAXOP];

/* ------ Stack Implementation ------ */
int sp = 0;
double val[MAXVAL];
bool isChar[MAXVAL];

/* ------ Main ------ */
int main() {
    int type;
    double op2;
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
        case 'E':
            push(exp(pop()));
            break;
        case 'W':
            push(sin(pop()));
            break;
        case 'R':
            op2 = pop();
            push(pow(pop(), op2));
            break;
        case 'D':
            duplicateTop();
            break;
        case 'S':
            swapTopTwo();
            break;
        case 'C':
            clearStack();   
            break; 
        case '=':
            op2 = pop(); 
            variables[last_var] = pop();
            break;
        case '\n':
            printTop();
            break;  
        case 'L':
            printf("Last printed: %f\n", last_print);
            break;
        default:
            if (type <= 'z' && type >= 'a') {
                last_var = type - 'a';
                push(variables[last_var]);
                break;
            }
            printf("error: unknown command %s\n", s);
            break;
        }
    }
    return 0;
}

/* ------ Stack Operations ------ */

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
    if (sp > 0) {
        last_print = val[sp-1];
        printf("%f\n", val[sp-1]);
    }
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

/* ------ Token Parser ------ */

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
            ;

    s[i] = '\0';
    ungetch(c);
    return NUMBER;
}

/* ------ Input Handling ------ */

int buf = 0;

int getch(void) {
    int c;
    if (buf != 0) {
        c = buf;
        buf = 0;
    }
    else {
        c = getchar();
    }
    return c;
}

void ungetch(int c) {
    if (c == EOF)
        return;
    else if (buf != 0)
        printf("ungetch: too many characters\n");
    else
        buf = c;
}

