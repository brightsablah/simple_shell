#include "shell.h"

void print_error(const char *program_name, const char *message) {
    write(STDERR_FILENO, program_name, strlen(program_name));
    write(STDERR_FILENO, ": ", 2);
    write(STDERR_FILENO, message, strlen(message));
    write(STDERR_FILENO, "\n", 1);
}
