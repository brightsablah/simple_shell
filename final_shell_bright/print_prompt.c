#include "shell.h"

/**
 * print_prompt - Print shell prompt
 *
 * Return: void
 */
void print_prompt(void)
{
	char prompt[] = "$ ";

	write(STDOUT_FILENO, prompt, sizeof(prompt));
}
