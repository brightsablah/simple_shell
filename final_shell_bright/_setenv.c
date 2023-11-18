#include "shell.h"


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
    int envSize;
    
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

    char **newEnviron = (char **)malloc((envSize + 2) * sizeof(char *));
    if (newEnviron == NULL) {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }

    /* Copy existing environment variables and free old env */
    for (int i = 0; i < envSize; i++) {
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

