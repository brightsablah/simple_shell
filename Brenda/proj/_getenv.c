#include "shell.h"

/**
 * _getenv - Retrieve value of environment variable
 * @name: Name of environment variable to retrieve
 *
 * Return: Value of the environment variable if found, NULL if not found
 */
char *_getenv(const char *name)
{
	char **env = environ;
	char *env_var;
	const char *name_ptr;
	size_t value_length;
	char *value;

	env_var = *env;

	while (*env)
	{
		name_ptr = name;
		while (*name_ptr && *env_var == *name_ptr)
		{
			env_var++;
			name_ptr++;
		}
		if (*name_ptr == '\0' && *env_var == '=')
		{
			env_var++; /* Move to the value part after '=' */

			value_length = _strlen(env_var);
			value = malloc(value_length + 1);

			if (value != NULL)
			{
				_strcpy(value, env_var);
				return (value);
			}
			else
			{
				return (NULL);
			}
		}
		env++;
		env_var = *env;
	}
	return (NULL);
}
