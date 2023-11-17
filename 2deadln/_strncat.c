#include "shell.h"

/**
 * _strncat - concentrates two strings
 * @dest: first string
 * @src: second string
 * @n: number of bytes used
 *
 * Return: pointer to the resulting string
 */
char *_strncat(char *dest, char *src, int n)
{
	int i = 0, len = 0;

	while (dest[i++])
		len++;

	for (i = 0; src[i] && i < n; i++)
		dest[len++] = src[i];

	return (dest);
}

