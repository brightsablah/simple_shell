#include "shell.h"

int execute_external_command(char *command, char **arguments)
{
    pid_t child_pid;

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
            perror("execve");
            exit(1);
        }
    } else
    {
        wait(NULL);
    }

    return 0;
}
