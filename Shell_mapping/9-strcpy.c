#include "main.h"
#include "main.h"

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
