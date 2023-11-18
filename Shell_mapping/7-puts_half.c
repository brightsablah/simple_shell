#include "main.h"

/**
 * puts_half - prints half a string
 * @str: string
 *
 * Return: void
 */
void puts_half(char *str)
{
	int a;
	int n;

	a = 0;
	while (str[a])
		a++;
	n = a / 2;
	if (a % 2)
		n += 1;
	while (n < a)
	{
		_putchar(str[n]);
		n++;
	}
	_putchar('\n');
}
