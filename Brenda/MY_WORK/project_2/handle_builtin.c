#include "shell.h"

// Function to handle echo command
void handle_echo(char **arguments) {
    int i = 0;
    while (arguments[i] != NULL) {
        printf("%s ", arguments[i]);
        i++;
    }
    printf("\n");
}

// Function to handle built-in commands
int handle_builtin(char *command, char **arguments) {
    if (_strcmp(command, "echo") == 0) {
        handle_echo(arguments);
        return 1; // Return 1 to indicate that it's a built-in command
    } else if (_strcmp(command, "env") == 0) {
        print_environment();
        return 1; // Return 1 to indicate that it's a built-in command
    }

    return 0; // Return 0 for non-built-in commands
}
