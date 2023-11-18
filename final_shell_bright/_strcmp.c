#include "shell.h"

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
