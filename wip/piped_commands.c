#include "shell.h"


void handlePipedCommands(const char *command) {
    char *extracted_command = NULL, *cleaned_command;
    size_t command_len = 0;
    int command_start = 0;  // Start from the beginning of the command
    int command_end = -1, i;

    // Find the end of the command
    for (i = 0; command[i] != '\0'; i++) {
        if (command[i] == '"') {
            command_end = i;
            break;
        }
    }

    if (command_end != -1) {
        command_len = command_end - command_start;
        extracted_command = malloc(command_len + 1);
        if (extracted_command != NULL) {
            strncpy(extracted_command, &command[command_start], command_len);
            extracted_command[command_len] = '\0';

            cleaned_command = remove_extra_spaces(extracted_command);
            if (cleaned_command != NULL) {
                if (is_executable(cleaned_command)) {
                    execute_command(cleaned_command);
                }
                free(cleaned_command);
            }
        }
    }
    if (extracted_command != NULL) {
        free(extracted_command);
    }
}

