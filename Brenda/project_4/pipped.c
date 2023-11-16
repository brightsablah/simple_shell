#include "shell.h"

/**
 * _memcpy - copies memory area
 * @dest: copied memory area
 * @src: memory area to copy
 * @n: number of bytes
 *
 * Return: pointer to dest
 */
char *_memcpy(char *dest, char *src, unsigned int n)
{
    unsigned int i;

    for (i = 0; i < n; i++)
    {
        *(dest + i) = *(src + i);
    }

    return (dest);
}

/**
 * executePipedCommands - Read and execute commands from standard input
 */
void executePipedCommands() {
    char buffer[BUFSIZ];
    char command_buffer[BUFSIZ];
    ssize_t bytes_read;
    int i = 0;
    int eof_flag = 0;

    while (((bytes_read = read(STDIN_FILENO, buffer, BUFSIZ)) > 0) && !eof_flag) {
        int start = 0;

        for (i = 0; i < bytes_read; ++i) {
            if (is_whitespace(buffer[i])) {
                if (i > start) {
                    _memcpy(command_buffer, &buffer[start], i - start);
                    command_buffer[i - start] = '\0';
                    execute_command(command_buffer);
                }
                start = i + 1;
            }
        }

        if (start < bytes_read) {
            _memcpy(command_buffer, &buffer[start], bytes_read - start);
            command_buffer[bytes_read - start] = '\0';
            execute_command(command_buffer);
        }

        if (bytes_read < BUFSIZ) {
            eof_flag = 1;
        }
    }

    exit(EXIT_SUCCESS);
}
