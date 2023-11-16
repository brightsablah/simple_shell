#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

char *_strncpy(char *dest, char *src, int n);
char *_getenv(const char *name);
int _strlen(char *s);
int main(void);

/**
 * _strncpy - copies a string
 * @dest: first string
 * @src: second string
 * @n: number of bytes used
 *
 * Return: copied string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i = 0, len = 0;

	while (src[i++])
		len++;

	for (i = 0; i < n && src[i]; i++)
		dest[i] = src[i];

	for (i = len; n > i; i++)
		dest[i] = '\0';

	return (dest);
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

char *_getenv(const char *name) {
    char **env = environ;

    while (*env) {
        char *env_var = *env;
        const char *name_ptr = name;
        char *equal_sign;
        char *value;
	int value_length;

        while (*name_ptr && *env_var == *name_ptr) {
            env_var++;
            name_ptr++;
        }

        if (*name_ptr == '\0' && *env_var == '=') {
            
            equal_sign = env_var;
            while (*equal_sign != '\0') {
                if (*equal_sign == '=') {
                    
                    equal_sign++;

		    value_length = _strlen(equal_sign);
                    value = (char *)malloc(value_length + 1);
                    if (value == NULL) {
                        return NULL;
                    }
                    _strncpy(value, equal_sign, value_length);
                    value[value_length] = '\0';
                    return value;
                }
                equal_sign++;
            }
        }
        env++;
    }
    return NULL;
}

int main(void) {
    const char *name = "PATH";
    char *value = _getenv(name);

    if (value != NULL) {
        printf("%s: %s\n", name, value);
        free(value);
    } else {
        printf("%s not found in the environment.\n", name);
    }

    return 0;
}
