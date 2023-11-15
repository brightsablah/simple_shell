#include "shell.h"

/**
 * _getenv - Get the value of an environment variable
 * @name: The name of the environment variable to retrieve
 *
 * Return: Value of the environment variable if found, NULL if not found
 */
char *_getenv(const char *name)
{
    char **env = environ;
    size_t value_length;
    char *value;

    while (*env) {
        const char *env_var = *env;
        const char *name_ptr = name;

        while (*name_ptr && *env_var == *name_ptr) {
            env_var++;
            name_ptr++;
        }

        if (*name_ptr == '\0' && *env_var == '=') {
            env_var++; /* Move to the value part after '=' */

            value_length = strlen(env_var);
            value = (char *)malloc(value_length + 1);

            if (value != NULL) {
                strcpy(value, env_var);
                return value;
            } else {
                return NULL; /* Handle memory allocation failure */
            }
        }
        env++;
    }
    return NULL; /* Return NULL if the variable is not found */
}
