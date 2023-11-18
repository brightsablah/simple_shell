#include "main.h"
#include "shell.h"

/**
 * linked_path - linked list of directories in a given environment variable
 * @name: name of environment variable
 *
 * Return: linked list of directories
 */
list_t *linked_path(char *name)
{
    
    char *path = _getenv(name);
    list_t *head = NULL;
    char *directory = path;
    char *current_char = path;

    if (path == NULL)
        return (NULL);
    while (*current_char != '\0')
    {
        if (*current_char == ':')
        {
            *current_char = '\0';
            add_node(&head, directory);
            directory = current_char + 1;
        }
        current_char++;
    }
    add_node(&head, directory);

    free(path);

    return (head);
}

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
