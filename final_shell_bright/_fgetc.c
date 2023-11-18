#include "shell.h"

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
