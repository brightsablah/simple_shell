#include "shell.h"


/**
 * _unsetenv - Delete a variable from the environment.
 * @name: Name of the environment variable to delete.
 *
 * Return: 0 on success, -1 on failure.
 */
int _unsetenv(const char *name) {
    if (name == NULL || *name == '\0' || strchr(name, '=') != NULL) {
        return -1; /* Invalid input */
    }

    /* Check if the variable exists */
    char *existingValue = _getenv(name);

    /* If the variable does not exist, do nothing */
    if (existingValue == NULL) {
        return 0;
    }

    /* Iterate through the environment variables to find the variable */
    char **env;
    for (env = environ; *env != NULL; env++) {
        /* Check if the current environment variable starts with the specified name */
        if (strncmp(*env, name, strlen(name)) == 0 && (*env)[strlen(name)] == '=') {
            /* Free the memory allocated for the environment variable */
            free(*env);

            /* Shift the remaining environment variables down to fill the gap */
            char **next = env + 1;
            while (*next != NULL) {
                *env++ = *next++;
            }
            *env = NULL;

            /* Now, free the memory for the environ array */
            
            return 0;
        }
    }

    return -1; /* Variable not found */
}

