#include "main.h"

/**
 * puts2 - prints every other character of a string, starting with the first
 * @str: string
 *
 * Return: 0 always (success)
 */
void puts2(char *str)
{
	int i = 0;
	int a = 0;

	while (str[i++])
		a++;

	for (i = 0; i < a; i = i + 2)
	{
		_putchar(str[i]);
	}
	_putchar('\n');
}
