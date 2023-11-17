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
