#include "shell.h"

list_t *linked_path(const char *name) {
    char *path = getenv(name);
    if (path == NULL) {
        printf("%s not found in the environment.\n", name);
        return NULL;
    }

    list_t *head = NULL;
    char *directory = path;
    char *current_char = path;

    while (*current_char != '\0') {
        if (*current_char == ':') {
            *current_char = '\0'; // Change ':' to '\0' temporarily
            add_node(&head, directory);
            directory = current_char + 1;
        }
        current_char++;
    }

    add_node(&head, directory); // Add the last directory

    return head;
}

/**
 * add_node - add new nod at the beginning of t_list
 * @head: node to check
 * @str: string to check
 *
 * Return: adress of new element
 */
list_t *add_node(list_t **head, const char *str)
{
	list_t *new_node;
	unsigned int dup_len = 0;
	char *dup;

	new_node = malloc(sizeof(list_t));
	if (new_node == NULL)
		return (NULL);

	dup = _strdup(str);
	if (dup == NULL)
	{
		free(new_node);
		return (NULL);
	}

	while (dup[dup_len] != '\0')
		dup_len++;

	new_node->str = dup;
	new_node->len = dup_len;
	new_node->next = *head;
	*head = new_node;

	return (new_node);
}

void find_command_in_path(const char *command) {
    list_t *path_directories = linked_path("PATH");
    list_t *current_directory = path_directories;

    while (current_directory != NULL) {
        char full_path[255]; // Adjust as per your maximum path length
        snprintf(full_path, sizeof(full_path), "%s/%s", current_directory->str, command);

        if (access(full_path, X_OK) == 0) {
            printf("Command found at: %s\n", full_path);
            break;
        }

        current_directory = current_directory->next;
    }

    if (current_directory == NULL) {
        printf("Command not found in the PATH.\n");
    }

    // Don't forget to free memory at the end
    current_directory = path_directories;
    while (current_directory != NULL) {
        list_t *temp = current_directory;
        current_directory = current_directory->next;
        free(temp->str);
        free(temp);
    }
}

int main() {
    find_command_in_path("ls"); // Replace "ls" with the command you want to find

    return 0;
}
