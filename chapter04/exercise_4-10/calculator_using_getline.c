#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

#define MAXOP   100
#define NUMBER  '0'
#define MAXVAL  100
#define LINELIM 1000

/* ------ Function Declarations ------ */
int getop(char []);
void push(double);
double pop(void);
void printTop(void);
void duplicateTop(void);
void swapTopTwo(void);
void clearStack(void);
int getline_mine(void);

/* ------ Global Variables ------ */
double variables[26];
int last_var = -1;
double last_print = 0.0;
char s[MAXOP];
int line_index = 0;
char line[LINELIM];

/* ------ Stack Implementation ------ */
int sp = 0;
double val[MAXVAL];

/* ------ Main ------ */
int main() {
    int type;
    double op2;

    while (getline_mine() > 0) {
        line_index = 0;  // reset index for the new line

        while ((type = getop(s)) != '\n' && type != '\0') {
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
                if ((int)op2 != 0)
                    push(fmod(pop(), op2));
                else
                    printf("error: divide by zero in modulus\n");
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
            case 'L':
                printf("Last printed: %f\n", last_print);
                break;
            default:
                if (type >= 'a' && type <= 'z') {
                    last_var = type - 'a';
                    push(variables[last_var]);
                } else {
                    printf("error: unknown command %s\n", s);
                }
                break;
            }
        }
        printTop(); // print result at the end of each line
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
        last_print = val[sp - 1];
        printf("\t%.8g\n", val[sp - 1]);
    } else
        printf("error: stack empty\n");
}

void duplicateTop(void) {
    if (sp > 0)
        push(val[sp - 1]);
    else
        printf("error: no elements to duplicate\n");
}

void swapTopTwo(void) {
    if (sp > 1) {
        double a = pop();
        double b = pop();
        push(a);
        push(b);
    } else
        printf("error: not enough elements to swap\n");
}

void clearStack(void) {
    sp = 0;
}

/* ------ Token Parser (Fixed) ------ */
int getop(char s[]) {
    int i = 0;
    char c;

    // Skip spaces and tabs
    while ((c = line[line_index++]) == ' ' || c == '\t')
        ;

    if (c == '\0')      // End of string
        return '\n';
    if (c == '\n')      // End of line
        return '\n';

    s[0] = c;
    s[1] = '\0';

    if (!isdigit(c) && c != '.')
        return c;       // Not a number

    // Collect integer part
    while (isdigit(line[line_index]))
        s[++i] = line[line_index++];

    // Collect fraction part
    if (line[line_index] == '.') {
        s[++i] = line[line_index++];
        while (isdigit(line[line_index]))
            s[++i] = line[line_index++];
    }

    s[i + 1] = '\0';
    return NUMBER;
}

/* ------ getline_mine (Fixed) ------ */
int getline_mine(void) {
    int c, i;
    for (i = 0; i < LINELIM - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        line[i] = c;
    if (c == EOF && i == 0)
        return 0; // end of input
    if (c == '\n')
        line[i++] = '\n';
    line[i] = '\0';
    return i;
}

