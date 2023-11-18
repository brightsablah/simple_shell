#include "shell.h"

/**
 * wordcount - Counts words in a string based on a delimiter
 * @s: The string to count words from
 * @delimiter: The delimiter character
 *
 * Return: The count of words in the string
 */
int wordcount(char *s, char *delimiter)
{
	int i, count = 0, in_word = 0;

	for (i = 0; s[i]; i++)
	{
		if (_strchr(delimiter, s[i]))
		{
			if (in_word)
			{
				in_word = 0;
				count++;
			}
		} else {
			in_word = 1;
		}
	}
	if (in_word)
	{
		count++;
	}
	return (count);
}
