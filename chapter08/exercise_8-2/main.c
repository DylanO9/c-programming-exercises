#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define OPEN_MAX    20
#define PERMS       0666    /* RW for owner, group, others */
#define BUFSIZE     1024

typedef struct _iobuf {
    int cnt;            /* characters left */
    char *ptr;          /* next character position */
    char *base;         /* location of buffer */
    int read_flag;      /* file open for reading */
    int write_flag;     /* file open for writing */
    int unbuf_flag;     /* file is unbuffered */
    int eof_flag;       /* EOF has occured on this file */
    int err_flag;       /* error has occured in the file */
    int fd;             /* file descriptor */
} FILE;

FILE _iob[OPEN_MAX];

FILE *fopen(char *, char *);
int _fillbuf(FILE *);

int main(void) {
    FILE *fp;
    int c;

    fp = fopen("test.txt", "r");
    if (fp == NULL) {
        perror("fopen failed");
        return 1;
    }

    printf("Reading file contents:\n\n");

    while ((c = _fillbuf(fp)) != EOF) {
        putchar(c);
    }

    if (fp->err_flag)
        printf("\n[Error occurred during read]\n");
    else if (fp->eof_flag)
        printf("\n[EOF reached]\n");

    close(fp->fd);
    free(fp->base);
    return 0;
}

FILE *fopen(char *name, char *mode) {
    int fd;
    FILE *fp;
    
    // Check if we have a valid mode
    if (*mode != 'r' && *mode != 'w' && *mode != 'a') 
        return NULL;
    
    // Check if we have a slot open in our _iob
    for (fp = _iob; fp < _iob + OPEN_MAX; fp++) {
        if (fp->read_flag == 0 && fp->write_flag == 0)
            break;
    }
    
    // No slot was found in _iob
    if (fp >= _iob + OPEN_MAX)
        return NULL;    
    
    if (*mode == 'r') {
        fd = open(name, O_RDONLY, 0);     
    } else if (*mode == 'w') {
        fd = creat(name, PERMS);
    } else if (*mode == 'a') {
        if ((fd = open(name, O_WRONLY, 0)) == -1)
            fd = creat(name, PERMS);    
        lseek(fd, 0L, 2);
    }

    if (fd == -1)
        return NULL; 
     
    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL; 
    fp->read_flag = *mode == 'r' ? 1 : 0;
    fp->write_flag = *mode == 'w' || *mode == 'a' ? 1 : 0;
    fp->unbuf_flag = 0;
    fp->eof_flag = 0;
    fp->err_flag = 0;
    
    return fp;
}

int _fillbuf(FILE *fp) {
    int bufsize;

    // Check if there were any errors previously
    if (fp->eof_flag || fp->err_flag || !fp->read_flag) {
        return EOF;
    }
    bufsize = fp->unbuf_flag ? 1 : BUFSIZE;
    
    if (fp->base == NULL) {
        if((fp->base = (char *)malloc(bufsize)) == NULL)
            return EOF;
    }
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    
    // Not enough characters 
    if (--fp->cnt < 0) {
        if (fp->cnt == -1)
            fp->eof_flag = 1;
        else
            fp->err_flag = 1;
        fp->cnt = 0;
        return EOF;
    }
    
   return (unsigned char) *fp->ptr++;
}
