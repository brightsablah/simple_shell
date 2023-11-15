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

/**
 * _strspn - get lenght of a prefix substring
 * @s: string
 * @accept: number of allowed return byte
 *
 * Return:  number of accept bytes in initial segment
 */
unsigned int _strspn(char *s, char *accept)
{
	int i, j;

	for (i = 0; s[i]; i++)
	{
		for (j = 0; accept[j]; j++)
		{
			if (s[i] == accept[j])
				break;
		}
		if (!accept[j])
			break;
	}
	return (i);
}

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

/**
 * _strstr - locates a substring
 * @haystack: string to check
 * @needle: substring to find in a string
 *
 * Return: pointer to the beginning of the located substring
 * NULL if the substring is not found
 */
char *_strstr(char *haystack, char *needle)
{
	char *start;
	char *sub;

	while (*haystack != '\0')
	{
		start = haystack;
		sub = needle;

		while (*sub == *haystack && *haystack != 0 && *sub != 0)
		{
			haystack++;
			sub++;
		}
		if (*sub == 0)
			return (start);
		haystack = start + 1;
	}
	return (0);
}

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
