#include "shell.h"

/**
 * print_path_directories - Prints directories in a given path
 * @path: The path containing directories
 *
 * Return: None
 */
void print_path_directories(const char *path) {
    const char *directory = path;
    const char *current_char = path;

    while (*current_char != '\0') {
        if (*current_char == ':') {
            /* If ':' is found, write the directory */
            int length = current_char - directory;
            write(STDOUT_FILENO, directory, length);
            write(STDOUT_FILENO, "\n", 1);
            directory = current_char + 1;
        }
        current_char++;
    }

    /* Write the last directory after the loop */
    write(STDOUT_FILENO, directory, current_char - directory);
}

/**
 * print_environment - Prints the environment variables in the format of 'env' command
 *
 * Return: None
 */
void print_environment() {
    char **env = environ;
    while (*env) {
        write(STDOUT_FILENO, *env, _strlen(*env));
        write(STDOUT_FILENO, "\n", 1);
        env++;
    }
}
