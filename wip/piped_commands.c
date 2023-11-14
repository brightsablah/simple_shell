#include "shell.h"

void handlePipedCommands(const char *command) {
    char *extracted_command = NULL, *cleaned_command;
    size_t command_len = 0;

    // Copy the command to a separate buffer for tokenization
    char *command_copy = strdup(command);
    if (command_copy == NULL) {
        // Handle memory allocation failure
        return;
    }

    // Tokenize the command using strtok
    char *token = strtok(command_copy, " ");
    if (token == NULL) {
        // No command found, free the copy and return
        free(command_copy);
        return;
    }

    // Extract the first token as the command
    extracted_command = strdup(token);
    if (extracted_command == NULL) {
        // Handle memory allocation failure
        free(command_copy);
        return;
    }

    // Clean the extracted command
    cleaned_command = remove_extra_spaces(extracted_command);
    if (cleaned_command != NULL) {
        if (is_executable(cleaned_command)) {
            execute_command(cleaned_command);
        }
        free(cleaned_command);
    }

    // Free allocated memory
    free(command_copy);
    free(extracted_command);
}
