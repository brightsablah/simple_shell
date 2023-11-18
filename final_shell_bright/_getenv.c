#include "shell.h"

/**
 * _getenv - Get the value of an environment variable.
 * @name: Name of the environment variable.
 *
 * Return: Pointer to the value of the environment variable,
 * or NULL if the variable is not found.
 */
char *_getenv(const char *name) {
    char **env;
    
    if (name == NULL || *name == '\0') {
        return NULL; /* Invalid input */
    }

    /* Iterate through the environment variables */
    for (env = environ; *env != NULL; env++) {
        /* Check if the current environment variable starts with the specified name */
        if (strncmp(*env, name, strlen(name)) == 0 && (*env)[strlen(name)] == '=') {
            /* Return the value part of the environment variable */
            return *env + strlen(name) + 1;
        }
    }

    return NULL; /* Variable not found */
}

