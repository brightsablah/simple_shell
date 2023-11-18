#include "shell.h"

/**
 * _strchr - locate a character
 * @s: string
 * @c: character
 *
 * Return: pointer to character , NULL if character not found
 */
char *_strchr(char *s, char c)
{
	int i;

	for (i = 0; s[i] >= '\0'; i++)
	{
		if (s[i] == c)
			return (s + i);
	}

	return ('\0');
}
