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
