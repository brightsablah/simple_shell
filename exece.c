#include "shell.h"

/**
 * execute_command - carry out execution of given command
 * @command_string: command string to execute
 */
void execute_command(char *command_string)
{
    char *command, *arguments[MAX_ARGS];
    int token_count = 0, i = 0;
    int should_exit = 0;
    int exit_status = 0;

    while (command_string[i] != '\0' && token_count < MAX_ARGS) {
        while (command_string[i] == ' ') {
            i++;
        }

        if (command_string[i] == '\0') {
            break;
        }

        arguments[token_count] = &command_string[i];
        token_count++;

        while (command_string[i] != ' ' && command_string[i] != '\0') {
            i++;
        }

        if (command_string[i - 1] == '\n') {
            command_string[i - 1] = '\0';
        } else {
            command_string[i] = '\0';
        }

        if (token_count == 1) {
            command = arguments[0];
        }


        if (_strcmp(command, "exit") == 0) {
            should_exit = 1;
            if (i < _strlen(command_string)) {
                exit_status = _atoi(&command_string[i + 1]);
            }
        }

        i++;
    }

    arguments[token_count] = NULL;

    if (token_count == 0) {
        return;
    }

    if (should_exit) {
        exit(exit_status);
    }

    if (handle_builtin(command, arguments, command_string)) {
        return;
    }

printf("ABOUT TO SEARCH FOR COMMAND IN THE ABSOLUTE PATH");


    if (command[0] == '/' || command[0] == '.')
    {
            if (execute_absolute_path(command, arguments) != 0)
            {
                print_error(arguments[0], "command not found");
            }
    } else {
        find_command_in_path(command, arguments);
    }
}


void print_error(const char *program_name, const char *message) {
    write(STDERR_FILENO, program_name, strlen(program_name));
    write(STDERR_FILENO, ": ", 2);
    write(STDERR_FILENO, message, strlen(message));
    write(STDERR_FILENO, "\n", 1);
}


/**
 * execute_absolute_path - Execute a command specified by an absolute path
 * @command: Command to execute
 * @arguments: Arguments for the command
 */
int execute_absolute_path(char *command, char **arguments)
{
    pid_t child_pid;

    if (_strcmp(command, "exit") == 0)
    {
        exit_shell(arguments);
        return 0;
    }

    if (access(command, X_OK) == 0)
    {
        child_pid = fork();

        if (child_pid == -1)
        {
            perror("fork");
            return 1;
        }

        if (child_pid == 0)
        {
            if (execve(command, arguments, environ) == -1)
            {
                return 1;
            }
        }
        else
        {
            wait(NULL);
        }

        return 0;
    }

    return 1;
}

int execute_external_command(char *command, char **arguments)
{
    pid_t child_pid;

    child_pid = fork();

    if (child_pid == -1)
    {
        perror("fork");
        return 1;
    }

    if (child_pid == 0)
    {
        if (execve(command, arguments, environ) == -1)
        {
            perror("execve");
            exit(1);
        }
    } else
    {
        wait(NULL);
    }

    return 0;
}
