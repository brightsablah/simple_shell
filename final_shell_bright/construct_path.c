#include "shell.h"

/**
 * construct_path - Constructs full path of a command in given directory
 * @directory: directory path
 * @command: The command
 *
 * Return:constructed path
 */
char *construct_path(char *directory, char *command)
{
	size_t path_length = _strlen(directory) + _strlen(command) + 2; /* '\0' */
	char *full_path = malloc(path_length);

	if (full_path == NULL)
		return (NULL);

	_strcpy(full_path, directory);
	_strcat(full_path, "/");
	_strcat(full_path, command);

	return (full_path);
}
