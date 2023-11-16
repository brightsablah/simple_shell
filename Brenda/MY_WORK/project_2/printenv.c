#include "shell.h"

void print_path_directories(const char *path) {
    const char *directory = path;
    const char *current_char = path;

    while (*current_char != '\0') {
        if (*current_char == ':') {
            // If ':' is found, write the directory
            int length = current_char - directory;
            write(STDOUT_FILENO, directory, length);
            write(STDOUT_FILENO, "\n", 1);
            directory = current_char + 1;
        }
        current_char++;
    }

    // Write the last directory after the loop
    write(STDOUT_FILENO, directory, current_char - directory);
}

void print_environment() {
    char **env = environ;
    while (*env) {
        if (_strstr(*env, "PATH=") == *env) {
            // If the line starts with "PATH=", write the PATH variable and its directories
            write(STDOUT_FILENO, *env, _strlen(*env));
            write(STDOUT_FILENO, "\n", 1);
            const char *path = *env + 5; // Skip "PATH=" in the string
            print_path_directories(path);
        } else {
            // For other environment variables, just write them
            write(STDOUT_FILENO, *env, _strlen(*env));
            write(STDOUT_FILENO, "\n", 1);
        }
        env++;
    }
}
