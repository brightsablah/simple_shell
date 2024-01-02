#include "shell.h"

/**
 * print_environment - Print environment variables
 */
void print_environment(void)
{
/*    extern char **environ; */
    int len = 0, count = 0;

    while ((environ[len] != NULL) && (count < 8))
    {
        write(STDOUT_FILENO, environ[len], _strlen(environ[len]));
        write(STDOUT_FILENO, "\n", 1);
        len++;
			count++;
    }
/* printf("Count = %d\n", count); */
}

void exit_shell(char **arguments)
{
    int status = 0;

    if (arguments != NULL && arguments[1] != NULL)
    {
        status = _atoi(arguments[1]);
    }

    exit(status);
}

/**
 * change_directory - Change the current working directory
 * @arguments: Arguments for the cd command
 */
void change_directory(char **arguments)
{
	const char *home_directory = _getenv("HOME");
    if (arguments[1] == NULL)
    {
	    if (home_directory == NULL)
		    return;

	    if (chdir(home_directory) == -1)
		    perror("cd");
    }
    else
    {
        if (strcmp(arguments[1], "/") == 0)
        {
		if (chdir("/") == -1)
		    perror("cd");
        }
        else
        {
            if (chdir(arguments[1]) == -1)
            {
                perror("cd");
            }
        }
    }
}

int handle_builtin(char *command, char **arguments, char *command_string)
{
    if (_strcmp(command, "env") == 0)
    {
       print_environment();
    }
    else if (_strcmp(command, "exit") == 0)
    {
        exit_shell(arguments);
        free(command_string);
    }
    else if (_strcmp(command, "cd") == 0)
    {
        change_directory(arguments);
        free(command_string);
    }
    else if (_strcmp(command, "setenv") == 0)
    {
        if (arguments[1] != NULL && arguments[2] != NULL && arguments[3] == NULL)
        {
            if (setenv(arguments[1], arguments[2], 1) == -1)
            {
                perror("setenv");
            }
        }
        else
        {
            print_error(command, "usage: setenv VARIABLE VALUE");
        }
    }
    else if (_strcmp(command, "unsetenv") == 0)
    {
        if (arguments[1] != NULL && arguments[2] == NULL)
        {
            if (unsetenv(arguments[1]) == -1)
            {
                perror("unsetenv");
            }
        }
        else
        {
            print_error(command, "usage: unsetenv VARIABLE");
        }
    }
    return 0;
}
