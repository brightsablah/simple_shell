#include "shell.h"

/**
 * is_whitespace - checks for spaces
 * @str: character to check
 *
 * Return: 1 for space character , otherwise 0
 */
int is_whitespace(const char ch)
{
	return (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r');
}
