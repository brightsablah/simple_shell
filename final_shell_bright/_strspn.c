#include "shell.h"

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

