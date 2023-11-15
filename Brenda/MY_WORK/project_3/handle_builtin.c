#include "shell.h"

/**
 * handle_builtin - Handle built-in commands such as echo and env
 * @command: The command to be checked if it's a built-in command
 * @arguments: Arguments passed with the command
 *
 * Return: 1 if it's a built-in command, 0 otherwise
 */
int handle_builtin(char *command)
{
    if (_strcmp(command, "env") == 0)
    {
        print_environment();
        return (1); /* Return 1 to indicate that it's a built-in command */
    }

    return (0); /* Return 0 for non-built-in commands */
}
