#include "main.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern char **environ;

char *_getenv(const char *name);

typedef struct list_s {
    char *str;
    unsigned int len;
    struct list_s *next;
} list_t;

list_t *add_node(list_t **head, const char *str);

list_t *linked_path(const char *name) {
    char *path = _getenv(name);

    if (path != NULL) {
        list_t *head = NULL; // Initialize the linked list
        char *directory = path;
        char *current_char = path;

        while (*current_char != '\0') {
            if (*current_char == ':') {
                // If ':' is found, add the directory to the linked list
                add_node(&head, directory);
                directory = current_char + 1;
            }
            current_char++;
        }

        // Add the last directory to the linked list
        add_node(&head, directory);

        return head;
    } else {
        printf("%s not found in the environment.\n", name);
        return NULL;
    }
}

int main(void) {
    const char *name = "PATH";
    list_t *directories = linked_path(name);

    if (directories != NULL) {
        // Now, 'directories' points to the head of the linked list containing directories

        // You can traverse and manipulate the linked list as needed

        // Free the linked list when done
        while (directories) {
            list_t *temp = directories;
            directories = directories->next;
            free(temp->str);
            free(temp);
        }
    }

    return 0;
}

/**
 * _getenv - retrieves an environment variable
 * @name: the name of the environment variable
 *
 * Return: a pointer to the value of the environment variable, or NULL if not found.
 */
char *_getenv(const char *name) {
    char **env = environ;

    while (*env) {
        if (strncmp(*env, name, strlen(name)) == 0) {
            char *equal_sign = strchr(*env, '=');
            if (equal_sign != NULL) {
                return equal_sign + 1;
            }
        }
        env++;
    }
    return NULL;
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

	dup = strdup(str);
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
