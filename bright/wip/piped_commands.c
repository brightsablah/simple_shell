#include "shell.h"

void handlePipedCommands(const char *command) {
    char *extracted_command = NULL, *cleaned_command;
    size_t command_len = 0;
    int command_start = 0;
    int command_end = -1, i;

    // Find the first non-space character
    while (command[command_start] == ' ') {
        command_start++;
    }

    // Find the end of the command (space or end of string)
    for (i = command_start; command[i] != '\0'; i++) {
        if (command[i] == ' ') {
            break;
        }
    }

    command_end = i;

    // Handle the case where there are leading spaces but no command
    if (command_start >= command_end) {
        return;
    }

    command_len = command_end - command_start;
    extracted_command = malloc(command_len + 1);
    if (extracted_command != NULL) {
        strncpy(extracted_command, &command[command_start], command_len);
        extracted_command[command_len] = '\0';

        // Allocate memory for a cleaned version without leading spaces
        cleaned_command = malloc((command_len + 1) * sizeof(char));
        if (cleaned_command != NULL) {
            strcpy(cleaned_command, extracted_command);

            if (is_executable(cleaned_command)) {
                execute_command(cleaned_command);
            }

            free(cleaned_command);
        }
    }

    if (extracted_command != NULL) {
        free(extracted_command);
    }
}
