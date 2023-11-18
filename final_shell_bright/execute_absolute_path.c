#include "shell.h"

/**
 * execute_absolute_path - Execute a command specified by an absolute path
 * @command: Command to execute
 * @arguments: Arguments for the command
 */
int execute_absolute_path(char *command, char **arguments)
{
    pid_t child_pid;

    if (_strcmp(command, "exit") == 0)
    {
        exit_shell(arguments);
        return 0;
    }

    if (access(command, X_OK) == 0)
    {
        child_pid = fork();

        if (child_pid == -1)
        {
            perror("fork");
            return 1;
        }

        if (child_pid == 0)
        {
            if (execve(command, arguments, environ) == -1)
            {
                return 1;
            }
        }
        else
        {
            wait(NULL);
        }

        return 0;
    }

    return 1;
}

