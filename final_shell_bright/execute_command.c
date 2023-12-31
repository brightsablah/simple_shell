#include "shell.h"

/**
 * execute_command - carry out execution of given command
 * @command_string: command string to execute
 */
void execute_command(char *command_string)
{
    char *command, *arguments[MAX_ARGS];
    int token_count = 0, i = 0;
    int should_exit = 0;
    int exit_status = 0;

    while (command_string[i] != '\0' && token_count < MAX_ARGS) {
        while (command_string[i] == ' ') {
            i++;
        }

        if (command_string[i] == '\0') {
            break;
        }

        arguments[token_count] = &command_string[i];
        token_count++;

        while (command_string[i] != ' ' && command_string[i] != '\0') {
            i++;
        }

        if (command_string[i - 1] == '\n') {
            command_string[i - 1] = '\0';
        } else {
            command_string[i] = '\0';
        }

        if (token_count == 1) {
            command = arguments[0];
        }


        if (_strcmp(command, "exit") == 0) {
            should_exit = 1;
            if (i < _strlen(command_string)) {
                exit_status = _atoi(&command_string[i + 1]);
            }
        }

        i++;
    }

    arguments[token_count] = NULL;

    if (token_count == 0) {
        return;
    }

    if (should_exit) {
        exit(exit_status);
    }

    if (handle_builtin(command, arguments, command_string)) {
        return;
    }

    if (command[0] == '/' || command[0] == '.')
    {
            if (execute_absolute_path(command, arguments) != 0)
            {
                print_error(arguments[0], "command not found");
            }
    } else {
        find_command_in_path(command, arguments);
    }
}

