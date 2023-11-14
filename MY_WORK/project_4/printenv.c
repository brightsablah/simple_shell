#include "shell.h"

/**
 * print_path_directories - Prints directories in a given path
 * @path: path containing directories
 *
 * Return: None
 */
void print_path_directories(const char *path)
{
	const char *directory = path;
	const char *current_char = path;
	int length;

	while (*current_char != '\0')
	{
		if (*current_char == ':')
		{
			length = current_char - directory;
			write(STDOUT_FILENO, directory, length);
			write(STDOUT_FILENO, "\n", 1);
			directory = current_char + 1;
		}
		current_char++;
	}
	write(STDOUT_FILENO, directory, current_char - directory);
}
