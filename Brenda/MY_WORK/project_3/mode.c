#include "shell.h"

/**
 * is_executable - Checks if a file is executable
 * @path: The file path
 *
 * Return: 1 if the file is executable, otherwise 0
 */
int is_executable(const char *path) {
    struct stat st;

    if (path == NULL || *path == '\0') {
        return 0;
    }

    if (stat(path, &st) == 0) {
        if (S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR)) {
            return 1; /* Executable file */
        }
    }

    return 0; /* Not an executable file */
}
int is_whitespace(const char *str) {
    while (*str) {
        if (*str != ' ' && *str != '\t' && *str != '\n' && *str != '\r') {
            return 0;
        }
        str++;
    }
    return 1; /* Only contains whitespace characters */
}

char* remove_extra_spaces(const char* line)
{
	int i, j;
	int space_flag;
	char* cleaned_line;
    if (line == NULL || *line == '\0') {
        return NULL;
    }

    cleaned_line = malloc(strlen(line) + 1);
    if (cleaned_line == NULL) {
        return NULL;
    }

    space_flag = 0; /* Flag to handle multiple spaces */

    for (i = 0, j = 0; line[i] != '\0'; i++) {
        if (line[i] != ' ') {
            cleaned_line[j++] = line[i];
            space_flag = 0; 
        } else {
            if (space_flag == 0) {
                cleaned_line[j++] = line[i];
            }
            space_flag = 1;
        }
    }

    cleaned_line[j] = '\0';
    return cleaned_line;
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
    char *cleaned_line;

    while ((read = getline(&line, &len, script)) != -1) {
        if (is_whitespace(line)) {
            return; /* Skip execution for empty or whitespace-only lines */
        }
        if (read > 1) {
            if (line[read - 1] == '\n') {
                line[read - 1] = '\0';
            }

            cleaned_line = remove_extra_spaces(line);
            if (cleaned_line != NULL) {
                if (is_executable(cleaned_line)) {
                    execute_command(cleaned_line);
                }
                free(cleaned_line);
            }
        }
    }

    free(line);
}
