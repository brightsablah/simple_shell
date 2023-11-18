#include "shell.h"

/**
 * main - Entry point to the shell
 * @argc: number of arguments
 * @argv: The argument values
 *
 * Return: 0 on successful exit, 1 on error
 */
int main(int argc, char *argv[])
{
    char *command_string = NULL;
    size_t com_len = 0;
    ssize_t readline;
    FILE *script;

    if (argc > 1)
    {
        script = fopen(argv[1], "r");
        if (script != NULL)
        {
            nonInteractiveMode(script);
            fclose(script);
        }
        else
        {
            print_error(argv[0], "failed to open script file");
            return 1;
        }
    }
    else
    {
        while (1)
        {
            if (isatty(STDIN_FILENO))
            {
                print_prompt();
            }
            readline = _getline(&command_string, &com_len, stdin);
            if (readline == -1)
            {
		free(command_string);  /* Free memory if getline fails */
		command_string = NULL;
		    printf("command string freed. program about to exit");
                exit(0);
                /* break;*/
            }

            if (readline > 1)
            {
                if (command_string[readline - 1] == '\n')
                    command_string[readline - 1] = '\0';

                execute_command(command_string);
            }
            free(command_string);
            command_string = NULL;
        }
    }

    return 0;
}
