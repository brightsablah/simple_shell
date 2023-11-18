#include "shell.h"

/**
 * find_command_in_path - find commands in specified PATH
 * @command: searched command
 * @arguments: Arguments for the command
 *
 * Return: Void
 */
void find_command_in_path(char *command, char **arguments)
{
	list_t *path_directories = linked_path("PATH");
	list_t *current_directory = path_directories;
	char *full_path;

	while (current_directory != NULL)
	{
		full_path = construct_path(current_directory->str, command);

		if (full_path != NULL && access(full_path, X_OK) == 0)
		{
			execute_absolute_path(full_path, arguments);
			free(full_path);
			free_list(path_directories);
			return;
		}
		free(full_path);
		current_directory = current_directory->next;
	}
	free_list(path_directories);
}
