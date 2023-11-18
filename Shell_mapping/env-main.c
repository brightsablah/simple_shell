#include "main.h"
#include <stdio.h>

/**
 * main - prints the environment
 *
 * Return: Always 0.
 */
int main(int argc, char *argv[], char **env)
{
	int len;

	for (len = 0; env[len] != NULL; len++)
	{
		printf("%s\n", env[len]);
	}
/*
	printf("My adress is : %p\n", (void *)env);
*/
	return (0);
}
