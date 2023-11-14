#include "shell.h"

void handlePipedCommands(const char *command) {
    char *cleaned_command = remove_extra_spaces(command);
    if (cleaned_command != NULL) {
        if (is_executable(cleaned_command)) {
            execute_command(cleaned_command);
        }
        free(cleaned_command);
    }
}
