#include <stdio.h>

int main(void) {
    FILE *fp;
    int c;

    fp = fopen("test.txt", "r");
    if (fp == NULL) {
        perror("fopen failed");
        return 1;
    }

    printf("Reading file contents:\n\n");
    while ((c = fgetc(fp)) != EOF)
        putchar(c);

    if (feof(fp))
        printf("\n[EOF reached]\n");
    else if (ferror(fp))
        printf("\n[Error occurred]\n");

    fclose(fp);
    return 0;
}

