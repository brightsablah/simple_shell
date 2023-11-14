#include "shell.h"


void handlePipedCommands(const char *command) {
    // Remove leading and trailing spaces
    char *cleaned_command = remove_extra_spaces(command);

    char *tokens[MAX_ARGS];
    int token_count = 0;

    // Tokenize the cleaned command based on spaces
    char *token = strtok(cleaned_command, " ");
    while (token != NULL && token_count < MAX_ARGS) {
        tokens[token_count++] = token;
        token = strtok(NULL, " ");
    }

    // Execute each token as a separate command
    for (int i = 0; i < token_count; ++i) {
        if (is_executable(tokens[i])) {
            execute_command(tokens[i]);
        }
    }

    free(cleaned_command);
}
