#include "shell.h"

// Function to remove trailing spaces from a string
void trim_trailing_spaces(char *str) {
    int i = strlen(str) - 1;
    while (i >= 0 && (str[i] == ' ' || str[i] == '\t')) {
        str[i] = '\0';
        i--;
    }

   // printf("command_string after removing trailing space = %s", str);
}


/**
 * print_prompt - Prints the shell prompt
 *
 * Return: None
 */
void print_prompt() {
    char prompt[] = "$ ";
    write(STDOUT_FILENO, prompt, sizeof(prompt));
}

/**
 * exit_shell - Exits the shell if the command is "exit"
 * @command_string: The command string
 *
 * Return: None
 */
void exit_shell(char *command_string) {
    if (_strcmp(command_string, "exit") == 0) {
        exit(0);
    }
}

/**
 * main - The main function to run the shell
 * @argc: The argument count
 * @argv: The argument values
 *
 * Return: 0 on successful exit, 1 on error
 */
int main(int argc, char *argv[]) {
    if (isatty(STDIN_FILENO)) {
        /* Interactive mode */
        char *command_string = NULL;
        size_t command_len = 0;
        ssize_t readline;

        while (1) {
            print_prompt();

            readline = getline(&command_string, &command_len, stdin);

            if (readline == -1) {
                exit_shell(NULL); /* No exit status */
                break;
            }

            if (readline > 1) {
                if (command_string[readline - 1] == '\n') {
                    command_string[readline - 1] = '\0';
                }
// Trim trailing spaces before processing the command
            trim_trailing_spaces(command_string);
                
                if (_strcmp(command_string, "exit") == 0) {
                    exit_shell(command_string);
                    break;
                } else {
                    execute_command(command_string);
                }
            }
        }

        free(command_string);
    } else {
        /* Non-interactive mode */
        if (argc > 1) {
            FILE *script = fopen(argv[1], "r");
            if (script != NULL) {
                nonInteractiveMode(script);
                fclose(script);
            } else {
                return 1;
            }
        } else {
            /* Check if data is being piped in */
            nonInteractiveMode(stdin);
        }
    }

    return 0;
}
