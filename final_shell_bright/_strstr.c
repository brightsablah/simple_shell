#include "shell.h"

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
