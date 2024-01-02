#include "shell.h"

void print_current_environment(void)
{
    char **env_var = environ;

    while (*env_var)
    {
        _puts(*env_var);
        env_var++;
    }
}



/**
 * _setenv - Change or add an environment variable.
 * @name: Name of the environment variable.
 * @value: Value to set for the environment variable.
 * @overwrite: Flag to determine whether to overwrite an existing variable.
 *
 * Return: 0 on success, -1 on failure.
 */
int _setenv(const char *name, const char *value, int overwrite) {
char *existingValue;
    char *newEnvVar;
    size_t envVarLength;
    int envSize, i;
    char **newEnviron;
    
    if (name == NULL || *name == '\0' || strchr(name, '=') != NULL) {
        return -1; /* Invalid input */
    }

    /* Check if the variable already exists */
    existingValue = _getenv(name);

    /* If the variable exists and overwrite is 0, do nothing */
    if (existingValue != NULL && !overwrite) {
        return 0;
    }

    /* Concatenate name=value into a single string */
    envVarLength = strlen(name) + strlen(value) + 2; /* +2 for '=' and null terminator */
    newEnvVar = (char *)malloc(envVarLength);
    if (newEnvVar == NULL) {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }
    snprintf(newEnvVar, envVarLength, "%s=%s", name, value);

    /* Update the environment by reallocating and copying */
    envSize = 0;
    while (environ[envSize] != NULL) {
        envSize++;
    }

    newEnviron = (char **)malloc((envSize + 2) * sizeof(char *));
    if (newEnviron == NULL) {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }

    /* Copy existing environment variables and free old env */
    for (i = 0; i < envSize; i++) {
        newEnviron[i] = environ[i];
    }
    /* free(environ); */

    /* Add the new environment variable */
    newEnviron[envSize] = newEnvVar;
    newEnviron[envSize + 1] = NULL;

    /* Update the global environ pointer */
    environ = newEnviron;

    return 0;
}


/**
 * _unsetenv - Delete a variable from the environment.
 * @name: Name of the environment variable to delete.
 *
 * Return: 0 on success, -1 on failure.
 */
int _unsetenv(const char *name) {
char *existingValue;
char **env;
    char **next;
    
    if (name == NULL || *name == '\0' || strchr(name, '=') != NULL) {
        return -1; /* Invalid input */
    }

    /* Check if the variable exists */
    existingValue = _getenv(name);

    /* If the variable does not exist, do nothing */
    if (existingValue == NULL) {
        return 0;
    }

    /* Iterate through the environment variables to find the variable */
    
    for (env = environ; *env != NULL; env++) {
        /* Check if the current environment variable starts with the specified name */
        if (strncmp(*env, name, strlen(name)) == 0 && (*env)[strlen(name)] == '=') {
            /* Free the memory allocated for the environment variable */
            free(*env);

            /* Shift the remaining environment variables down to fill the gap */
            next = env + 1;
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

