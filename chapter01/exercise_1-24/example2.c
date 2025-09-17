#include <stdio.h>

int main() {
    printf("Hello, world!\n");   // OK

    if (1 > 0) {
        printf("Unclosed string...\n);   // ❌ missing closing quote
    }

    char c = 'a;   // ❌ unclosed char literal

    /* This is a comment
       that never closes...   // ❌ unclosed multiline comment

    int arr[3;   // ❌ missing closing bracket

    if (1 > 2)) {   // ❌ extra closing parenthesis
        printf("Oops!\n");
    }

    return 0;
}

