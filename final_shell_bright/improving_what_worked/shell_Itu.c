#include "shell.h"

void execute_script(FILE *script) {
    nonInteractiveMode(script);
}
/**
 * print_prompt - Print shell prompt
 *
 * Return: void
 */
void print_prompt(void)
{
	char prompt[] = "$ ";

	write(STDOUT_FILENO, prompt, sizeof(prompt));
}

char **command_string_tracker = NULL;

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
	command_string_tracker = &command_string;
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
	atexit(cleanup);
	    
        while (1)
        {
            if (isatty(STDIN_FILENO))
            {
                print_prompt();
            }
		
            readline = getline(&command_string, &com_len, stdin);
            if (readline == -1)
            {
		    free(command_string);  /* Free memory if getline fails */
                exit_shell(NULL);
                break;
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

void cleanup(void){
	if ((*command_string_tracker) != NULL) {
		free(*command_string_tracker)
			}
}
