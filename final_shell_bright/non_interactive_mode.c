#include "shell.h"

/**
 * nonInteractiveMode - Executes commands in non interacting mode
 * @script: The file to read commands from
 *
 * Return: None
 */
void nonInteractiveMode(FILE *script) {
	char *line = NULL, *cleaned_line;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, script)) != -1) {

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
