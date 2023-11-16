#include "shell.h"

/**
 * handle_builtin - Handle built-in commands
 * @command: built-in command
 *
 * Return: 1 for built-in command, 0 otherwise
 */
int handle_builtin(char *command)
{
	if (_strcmp(command, "env") == 0)
	{
		print_environment();
		return (1);
	}

	return (0);
}
