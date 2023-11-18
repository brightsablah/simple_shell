#include "shell.h"

/**
 * _strpbrk - search a string for any of a set of bytes
 * @s: string to check
 * @accept: string to check against
 *
 * Return: bytes in s matching bytes in accept
 * Null if no such byte is found
 */
char *_strpbrk(char *s, char *accept)
{
	int i;

	while (*s)
	{
		for (i = 0; accept[i]; i++)
		{
			if (*s == accept[i])
				return (s);
		}

		s++;
	}

	return ('\0');
}
