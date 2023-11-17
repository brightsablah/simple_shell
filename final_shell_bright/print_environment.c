#include "shell.h"

/**
 * print_environment - Print environment variables
 */
void print_environment(void)
{
    extern char **environ;
    int len = 0;

    while (environ[len] != NULL)
    {
        write(STDOUT_FILENO, environ[len], _strlen(environ[len]));
        write(STDOUT_FILENO, "\n", 1);
        len++;
    }
}
