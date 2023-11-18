#include "main.h"
#include "main.h"

/**
 * print_rev - print string in reverse
 * @s: string
 *
 * Return: string in reverse
 */
void print_rev(char *s)
{
	int i, b;

	for (i = 0; s[i] != '\0'; i++)
	{
		continue;
	}
	b = i - 1;
	for (i = b; i >= 0; i--)
	{
		_putchar(s[i]);
	}
	_putchar('\n');
}
