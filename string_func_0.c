#include "shell.h"

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * _strlen - returns leghth of a string
 * @s: string
 *
 * Return: lenght of a string
 */
int _strlen(char *s)
{
	int i;

	for (i = 0; s[i] != '\0'; i++)
	{
		continue;
	}

	return (i);
}

/**
 * _puts - prints a string
 * @str: string
 *
 * Return: 0 always (success)
 */
void _puts(char *str)
{
	int a;

	for (a = 0; str[a] != '\0'; a++)
	{
		_putchar(str[a]);
	}
	_putchar('\n');
}

/**
 * *_strcpy - copies a string pointed to by src
 * include the terminating null byte (\0)
 * copy to the buffer pointed to by dest
 * @dest: pointer
 * @src: pointer
 *
 * Return: pointer to dest
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

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
