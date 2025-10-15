#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 5000   /* max # of lines to be sorted */
#define MAXLEN 1000     /* max length of any input line */

char *lineptr[MAXLINES];   /* pointers to text lines */

int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);
void myqsort(void *v[], int left, int right, int (*comp)(void *, void *));
int numcmp(char *, char *);
int getLine(char *, int);

/* sort input lines */
int main(int argc, char *argv[])
{
    int nlines;            /* number of input lines read */
    int numeric = 0;       /* 1 if numeric sort */
    int reverse = 0;       /* 1 if reverse sort */

    /* check command-line flags */
    while (--argc > 0 && (*++argv)[0] == '-') {
        char *p = *argv;
        while (*++p) {
            if (*p == 'n')
                numeric = 1;
            else if (*p == 'r')
                reverse = 1;
            else {
                printf("sort: illegal option %c\n", *p);
                return 1;
            }
        }
    }

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        myqsort((void **) lineptr, 0, nlines - 1,
                (int (*)(void *, void *))(numeric ? (int (*)(void *, void *))numcmp
                                                 : (int (*)(void *, void *))strcmp));

        if (reverse) {
            for (int i = nlines - 1; i >= 0; i--)
                printf("%s\n", lineptr[i]);
        } else {
            writelines(lineptr, nlines);
        }
        return 0;
    } else {
        printf("input too big to sort\n");
        return 1;
    }
}

/* myqsort: sort v[left]...v[right] into increasing order */
void myqsort(void *v[], int left, int right, int (*comp)(void *, void *))
{
    int i, last;
    void swap(void *v[], int, int);

    if (left >= right)
        return;

    swap(v, left, (left + right)/2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if ((*comp)(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    myqsort(v, left, last - 1, comp);
    myqsort(v, last + 1, right, comp);
}

/* numcmp: compare s1 and s2 numerically */
int numcmp(char *s1, char *s2)
{
    double v1, v2;
    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

/* swap: interchange v[i] and v[j] */
void swap(void *v[], int i, int j)
{
    void *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = getLine(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = malloc(len)) == NULL)
            return -1;
        line[len-1] = '\0';   /* delete newline */
        strcpy(p, line);
        lineptr[nlines++] = p;
    }
    return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
    for (int i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}

/* getLine: read a line into s, return length */
int getLine(char *s, int lim)
{
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

