#include "shell.h"

/**
 * linked_path - Creates a linked list of directories based on a given environment variable
 * @name: The name of the environment variable
 *
 * Return: A linked list of directories
 */
list_t *linked_path(const char *name)
{
    char *path = _getenv(name);
    list_t *head = NULL;
    char *directory = path;
    char *current_char = path;

    if (path == NULL)
    {
	    printf("%s not found in the environment.\n", name);
	    return (NULL);
    }

    while (*current_char != '\0') {
        if (*current_char == ':') {
            *current_char = '\0'; /* Change ':' to '\0' temporarily */
            add_node(&head, directory);
            directory = current_char + 1;
        }
        current_char++;
    }

    add_node(&head, directory); /* Add the last directory */

    return head;
}

/**
 * find_command_in_path - Searches for a command in the directories specified in the PATH
 * @command: The command to search for
 * @arguments: Arguments for the command
 *
 * Return: None
 */
void find_command_in_path(char *command, char **arguments) {
    list_t *path_directories = linked_path("PATH");
    list_t *current_directory = path_directories;

    while (current_directory != NULL) {
        char *full_path = construct_path(current_directory->str, command);

        if (full_path != NULL && access(full_path, X_OK) == 0) {
            execute_absolute_path(full_path, arguments);
            free(full_path);
            return;
        }

        free(full_path);
        current_directory = current_directory->next;
    }

    /* Handling if the command is not found in the PATH */
    perror("Command not found in the PATH");

    /* Free memory at the end */
    free_list(path_directories);
}

/**
 * construct_path - Constructs the full path of a command in a given directory
 * @directory: The directory path
 * @command: The command
 *
 * Return: The constructed path
 */
char *construct_path(const char *directory, const char *command) {
    size_t path_length = strlen(directory) + strlen(command) + 2; /* +2 for '/' and null terminator */
    char *full_path = (char *)malloc(path_length);

    if (full_path == NULL) {
        perror("Memory allocation failed");
        return NULL;
    }

    strcpy(full_path, directory);
    strcat(full_path, "/");
    strcat(full_path, command);

    return full_path;
}
