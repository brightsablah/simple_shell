#include "shell.h"

/**
 * set_string - set value of pointer to a char
 * @to: pointer to string
 * @s: pointer to pointer to string
 *
 * Return: void
 */
void set_string(char **s, char *to)
{
	*s = to;
}
