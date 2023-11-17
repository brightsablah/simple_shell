#include "shell.h"

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

    return 0;
}
