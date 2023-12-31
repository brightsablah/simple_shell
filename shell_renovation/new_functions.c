#include "shell.h"

ssize_t _getline(char **lineptr, size_t *n, FILE *stream) {
  int ch;
  size_t i;
  static size_t buffer_size = BUFFER_SIZE;
    if (*lineptr == NULL || *n == 0) {
        /* Allocate initial buffer if not provided */
        *n = buffer_size;
        *lineptr = (char *)malloc(*n);
        if (*lineptr == NULL) {
            return -1;  /* Memory allocation failure */
        }
    }

    i = 0;

    /* Read characters until a newline or EOF is encountered */
    while ((ch = _fgetc(stream)) != EOF && ch != '\n') {
        /* Check if more space is needed */
        if (i == *n - 1) {
            *n *= 2;
            *lineptr = safe_realloc(*lineptr, i, *n);
        }

        /* Store the character */
        (*lineptr)[i++] = (char)ch;
    }

    /* Check if any characters were read */
    if (i == 0 && ch == EOF) {
        return 0;  /* End of file reached */
    }

    /* Null-terminate the string */
    (*lineptr)[i] = '\0';

    return i;  /* Number of characters read */
}


int _fgetc(FILE *stream) {
  char c;
  ssize_t bytesRead;

    /* Ensure that the stream is not NULL */
    if (stream == NULL) {
        return EOF;
    }

    bytesRead = read(fileno(stream), &c, 1);

    if (bytesRead == 1) {
        return (unsigned char)c;
    } else {
        return EOF; /* End of file or error */
    }
}


