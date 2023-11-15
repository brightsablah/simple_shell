#include "shell.h"

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * _strlen - returns leghth of a string
 * @s: string
 *
 * Return: lenght of a string
 */
int _strlen(char *s)
{
	int i;

	for (i = 0; s[i] != '\0'; i++)
	{
		continue;
	}

	return (i);
}

/**
 * _puts - prints a string
 * @str: string
 *
 * Return: 0 always (success)
 */
void _puts(char *str)
{
	int a;

	for (a = 0; str[a] != '\0'; a++)
	{
		_putchar(str[a]);
	}
	_putchar('\n');
}

/**
 * *_strcpy - copies a string pointed to by src
 * include the terminating null byte (\0)
 * copy to the buffer pointed to by dest
 * @dest: pointer
 * @src: pointer
 *
 * Return: pointer to dest
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char *_strdup(const char *str) {
    if (str == NULL) {
        return NULL; // Return NULL for NULL input
    }

    // Calculate the length of the input string
    size_t length = 0;
    while (str[length] != '\0') {
        length++;
    }

    // Allocate memory for the new string (including the null terminator)
    char *duplicate = (char *)malloc((length + 1) * sizeof(char));
    if (duplicate == NULL) {
        return NULL; // Return NULL if memory allocation fails
    }

    // Copy the characters from the input string to the new string
    for (size_t i = 0; i <= length; i++) {
        duplicate[i] = str[i];
    }

    return duplicate; // Return the duplicated string
}
