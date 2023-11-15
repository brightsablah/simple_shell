#include "shell.h"

/**
 * is_executable - Checks if a file is executable
 * @path: The file path
 *
 * Return: 1 if the file is executable, otherwise 0
 */
int is_executable(const char *path) {
    struct stat st;

    if (stat(path, &st) == 0) {
        if (S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR)) {
            return 1; /* Executable file */
        }
    }

    perror("Error");
    return 0; /* Not an executable file */
}

/**
 * nonInteractiveMode - Executes commands from a script file
 * @script: The file to read commands from
 *
 * Return: None
 */
void nonInteractiveMode(FILE *script) {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, script)) != -1) {
        if (read > 1) {
            if (line[read - 1] == '\n') {
                line[read - 1] = '\0';
            }

            if (is_executable(line)) {
                /* Only execute if the file is executable */
                execute_command(line);
            } else {
                perror("Error: Not an executable file");
            }
        }
    }

    free(line);
}
