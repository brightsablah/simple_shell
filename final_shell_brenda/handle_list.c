#include "main.h"
#include "main.h"
#include "shell.h"

/**
 * free_list - Frees a linked list
 * @head: Pointer to the head of the linked list
 *
 * Return: None
 */
void free_list(list_t *head)
{
	list_t *tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp->str);
		free(tmp);
	}
}

/**
 * add_node - Adds a new node at the beginning of a linked list
 * @head: Pointer to the head of the linked list
 * @str: String to be stored in the new node
 *
 * Return: Address of the new element
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
