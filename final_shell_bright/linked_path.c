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
