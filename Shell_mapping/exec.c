#include "main.h"
#include <stdio.h>
#include <unistd.h>

/**
 * main - execve example
 *
 * Return: Always 0.
 */
int main(int argc, char *argv[])
{
	char *default_argv[] = {"/bin/ls", "-l", NULL};
	char **new_argv = default_argv;

	if (argc == 2)
	{
		new_argv = (char *[]){"/bin/ls", "-l", argv[1], NULL};
	}

	if (execve(new_argv[0], new_argv, NULL) == -1)
	{
		perror("Error:");
	}

	return (0);
}
