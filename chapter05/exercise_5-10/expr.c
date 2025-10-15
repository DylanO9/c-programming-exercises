#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE 100

int is_number(const char *s) {
    if (!s || !*s) return 0;
    // optional leading minus
    int i = 0;
    if (s[0] == '-') {
        if (!isdigit((unsigned char)s[1])) return 0;
        i = 1;
    }
    for (; s[i]; i++) {
        if (!isdigit((unsigned char)s[i])) return 0;
    }
    return 1;
}

int main(int argc, char *argv[]) {
    int stack[MAX_SIZE];
    int sp = 0;

    if (argc < 2) {
        printf("Usage: expr <rpn tokens...>\n");
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        char *arg = argv[i];

        if (is_number(arg)) {
            if (sp >= MAX_SIZE) {
                printf("Error: stack overflow\n");
                return 1;
            }
            int val = atoi(arg);
            stack[sp++] = val;
            printf("Pushed %d\n", val);
        } else if (strlen(arg) == 1 && (arg[0] == '+' || arg[0] == '-' || arg[0] == '*' || arg[0] == '/')) {
            if (sp < 2) {
                printf("Error: not enough operands for '%s'\n", arg);
                return 1;
            }
            int op2 = stack[--sp];
            int op1 = stack[--sp];
            int result;
            switch (arg[0]) {
                case '+': result = op1 + op2; break;
                case '-': result = op1 - op2; break;
                case '*': result = op1 * op2; break;
                case '/': 
                    if (op2 == 0) {
                        printf("Error: division by zero\n");
                        return 1;
                    }
                    result = op1 / op2; 
                    break;
                default:
                    printf("Error: unknown operator '%s'\n", arg);
                    return 1;
            }
            printf("Computed %d %c %d = %d\n", op1, arg[0], op2, result);
            stack[sp++] = result;
        } else {
            printf("Error: invalid token '%s'\n", arg);
            return 1;
        }
    }

    if (sp != 1) {
        printf("Error: invalid expression (stack has %d elements)\n", sp);
        return 1;
    }

    printf("Answer: %d\n", stack[0]);
    return 0;
}

