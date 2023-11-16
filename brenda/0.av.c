#include <stdio.h>

/**
 * main -enty point
 * av: array of strings recieverd as arguments
 * ac: number of arguments
 */
int main (int __attribute__((unused)) argc, char *argv[])
{
	/* print only argument this excludes name used to evoke current programme */
	int count = 1;

	while (argv[count] != NULL)
	{
		printf( "%s\n", argv[count]);
		count++;
	}

	return (0);
}
