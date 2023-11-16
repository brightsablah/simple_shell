#include "shell.h"

/**
 * execute_command - carry out execution of given command
 * @command_string: command string to execute
 */
void execute_command(char *command_string)
{
    char *command, *arguments[MAX_ARGS];
    int token_count = 0, i = 0;

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

        i++;
    }

    arguments[token_count] = NULL;

    if (token_count == 0) {
        return;
    }
 
    if (handle_builtin(command, arguments)) {
        return;
    }

    if (command[0] == '/' || command[0] == '.') {
        execute_absolute_path(command, arguments);
    } else {
        find_command_in_path(command, arguments);
    }
}

/**
 * execute_absolute_path - Execute a command specified by an absolute path
 * @command: Command to execute
 * @arguments: Arguments for the command
 */
void execute_absolute_path(char *command, char **arguments)
{
	pid_t child_pid;

	if (access(command, X_OK) == 0)
	{
		child_pid = fork();

		if (child_pid == -1)
			return;

		if (child_pid == 0)
		{
			if (execve(command, arguments, environ) == -1)
				exit(1);
		}
		else
		{
			wait(NULL);
		}
		return;
	}
}
