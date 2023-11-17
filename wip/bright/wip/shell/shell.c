#include "shell.h"

#define MAX_INPUT_SIZE 1024
#define PROMPT "#cisfun$ "

void display_prompt() {
    if (isatty(STDIN_FILENO)) {
        printf("%s", PROMPT);
        fflush(stdout);
    }
}

int main() {
    char input[MAX_INPUT_SIZE];

    while (1) {
        display_prompt();

        // Read a line of input from the user
        if (fgets(input, sizeof(input), stdin) == NULL) {
            // Handle end of file (Ctrl+D)
            printf("\n");
            break;
        }

        // Remove newline character at the end
        input[strcspn(input, "\n")] = '\0';

        // Fork a new process
        pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process

            // Check if the command is being piped to
            if (isatty(STDIN_FILENO)) {
                // If not piped, execute the command normally
                execlp(input, input, (char *)NULL);

                // If execlp fails
                perror("exec");
                exit(EXIT_FAILURE);
            } else {
                // If piped, read from standard input and write to standard output
                char *args[] = { "/bin/sh", "-c", input, NULL };
                execvp("/bin/sh", args);

                // If execvp fails
                perror("execvp");
                exit(EXIT_FAILURE);
            }
        } else {
            // Parent process
            int status;
            waitpid(pid, &status, 0);

            if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE) {
                // Handle executable not found
                fprintf(stderr, "Command not found: %s\n", input);
            }
        }
    }

    return 0;
}
