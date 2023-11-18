#include "shell.h"

/**
 * *_strcat - concentrates two strings
 * @dest: first string
 * @src: second string
 *
 * Return: pointer to the resulting string
 */
char *_strcat(char *dest, char *src)
{
	char *ptr = dest;

	while (*dest != '\0')
	{
		dest++;
	}
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';

	return (ptr);
}

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

char *_strncpy(char *dest, char *src, int n)
{
	int i = 0, len = 0;

	while (src[i++])
		len++;

	for (i = 0; i < n && src[i]; i++)
		dest[i] = src[i];

	for (i = len; n > i; i++)
		dest[i] = '\0';

	return (dest);
}

/**
 * _strcmp - compare two strings
 * @s1: first string
 * @s2: second string
 *
 * Return: comparison (if less -,if greater +, if equal 0)
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

