#include "shell.h"

/**
 * _strdup - Duplicates a string
 * @str: The string to duplicate
 *
 * Return: pointer to duplicated string,otherwise return NULL
 */
char *_strdup(const char *str)
{
	int len = 0, i = 0;
	char *duplicate;

	if (str == NULL)
		return (NULL);

	while (str[len] != '\0')
		len++;

	duplicate = malloc((len + 1) * sizeof(char));
	if (duplicate == NULL)
	{
		
		return (NULL);
	}

	for (i = 0; i <= len; i++)
	{
		duplicate[i] = str[i];
	}

	return (duplicate); /* Return the duplicated string */
}
