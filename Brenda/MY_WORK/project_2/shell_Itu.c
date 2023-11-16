#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

#define MAX_ARGS 10
#define MAX_COMMAND_SIZE 100

void parse_input(char *input, char *command, char *args[MAX_ARGS], size_t args_size) {
    memset(command, 0, MAX_COMMAND_SIZE);
    memset(args, 0, args_size);

    char *token = strtok(input, " ");
    if (token != NULL) {
        strncpy(command, token, MAX_COMMAND_SIZE - 1);  // Store the command as the first argument
        args[0] = command;  // Set the first argument as the command itself

        int arg_index = 1;
        while ((token = strtok(NULL, " ")) != NULL && arg_index < MAX_ARGS - 1) {
            args[arg_index] = strdup(token);
            arg_index++;
        }
    }
}

void execute_command(char *command, char *args[]) {
    pid_t pid = fork();

    if (pid == -1) {
        perror("Fork failed");
        _exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        if (access(command, X_OK) == 0) {
            // Execute the command with its absolute path
            execv(command, args);
        } else {
            // Command not found or not executable
            perror("Command execution failed");
            _exit(EXIT_FAILURE);
        }
    } else {
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            if (WEXITSTATUS(status) != 0) {
                char error_message[] = "Command exited with non-zero status\n";
                write(STDERR_FILENO, error_message, sizeof(error_message) - 1);
            }
        } else if (WIFSIGNALED(status)) {
            char error_message[] = "Command terminated by signal\n";
            write(STDERR_FILENO, error_message, sizeof(error_message) - 1);
        }
    }
}

void print_prompt() {
    char prompt[] = "$ ";
    write(STDOUT_FILENO, prompt, sizeof(prompt) - 1);
}

void exit_shell(int sig) {
    switch (sig) {
        case SIGINT:
            write(STDOUT_FILENO, "\nCaught SIGINT (Ctrl+C), exiting shell...\n", sizeof("\nCaught SIGINT (Ctrl+C), exiting shell...\n"));
            break;
        case SIGHUP:
            write(STDOUT_FILENO, "\nCaught SIGHUP (Ctrl+D), exiting shell...\n", sizeof("\nCaught SIGHUP (Ctrl+D), exiting shell...\n"));
            break;
        default:
            write(STDOUT_FILENO, "\nReceived unknown signal, exiting shell...\n", sizeof("\nReceived unknown signal, exiting shell...\n"));
    }
    exit(0);
}

int main(void) {
    char *command_string = NULL;
    size_t command_len = 0;
    ssize_t readline;

    while (1) {
        print_prompt();

        // Use getline to read user input
        readline = getline(&command_string, &command_len, stdin);

        if (readline == -1) {
            exit_shell(0);
            break;
        }

        if (readline > 1) {
            // Remove the newline character
            if (command_string[readline - 1] == '\n') {
                command_string[readline - 1] = '\0';
            }

            // Parse the input
            char command[MAX_COMMAND_SIZE];
            char *args[MAX_ARGS];
            parse_input(command_string, command, args, sizeof(args));

            // Execute the command
            execute_command(command, args);
        }
    }

    free(command_string);
    return 0;
}
