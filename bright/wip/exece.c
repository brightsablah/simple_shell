#include "shell.h"

/**
 * execute_command - Executes the provided command
 * @command_string: String containing the command to execute
 */
void execute_command(char *command_string) {

       char *command, **arguments;
    char *tokens[MAX_ARGS];
    int token_count = 0;
    int i = 0;

    /* Tokenizing the command string based on spaces */
    while (command_string[i] != '\0' && token_count < MAX_ARGS) {
        while (command_string[i] == ' ') {
                /* Skip over multiple spaces until a non-space character is found */
            i++;
        }

        if (command_string[i] == '\0') {
                /* Handle empty command (only spaces) */
        return;
    }
            tokens[token_count] = &command_string[i];
        
        while (command_string[i] != ' ' && command_string[i] != '\0') {
            i++;
        }
        if (command_string[i - 1] == '\n') {
            command_string[i - 1] = '\0';
        } else {
            command_string[i] = '\0';
        }
        token_count++;
        i++;
    }

    tokens[token_count] = NULL;

    if (token_count == 0) {
        return; /* If no tokens were found, just return without an error message */
    }

    command = tokens[0];
    arguments = tokens;

    if (handle_builtin(command)) {
        return; /* If it's a built-in command, return without forking */
    }

    /* Check if it's an absolute path or in the current directory */
    if (command[0] == '/' || command[0] == '.') {
        execute_absolute_path(command, arguments);
        return;
    }

    /* If not an absolute path or known command, search in the directories specified in the PATH */
    if (!find_command_in_path(command, arguments) && !is_executable(command))
    {
       /* if control reaches here, the command was not found */
           fprintf(stderr, "%s: command not found\n", command);
    }
}

/**
 * execute_absolute_path - Execute a command specified by an absolute path
 * @command: Command to execute
 * @arguments: Arguments for the command
 */
void execute_absolute_path(char *command, char **arguments)
{
    if (access(command, X_OK) == 0) {
        pid_t child_pid = fork();
        if (child_pid == -1) {
            return;
        }

        if (child_pid == 0) {

            if (execve(command, arguments, environ) == -1) {
                exit(1);
            }
        } else {
            wait(NULL);
            return;
        }
    }
}
