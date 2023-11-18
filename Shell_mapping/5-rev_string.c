#include "main.h"
#include "main.h"

/**
 * rev_string - print string in reverse
 * @s: string
 *
 * Return: string in reverse
 */
void rev_string(char *s)
{
	int i = 0;
	int a = 0;
	char tmp;

	while (s[i++])
		a++;
	for (i = a - 1; i >= a / 2; i--)
	{
		tmp = s[i];
		s[i] = s[a - i - 1];
		s[a - i - 1] = tmp;
	}
}
