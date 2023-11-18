#include "main.h"

/**
 * swap_int - swap the value of two intergers
 * @a: first value
 * @b: second value
 *
 * Return: 0 always (success)
 */
void swap_int(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
