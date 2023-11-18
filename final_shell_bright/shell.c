#include "shell.h"

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
    size_t com_len = 0;
    ssize_t readline;
    FILE *script;
	 struct sigaction sa;
	command_string_tracker = &command_string;

    if (argc > 1)
    {
        script = fopen(argv[1], "r");
        if (script != NULL)
        {
            nonInteractiveMode(script);
            fclose(script);
		return (0);
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

	

	/* Set up signal handling for SIGINT */
   
    sa.sa_handler = handle_sigint;
    sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);  /* Initialize sa_mask to an empty signal set*/
    sigaction(SIGINT, &sa, NULL);
		
            readline = _getline(&command_string, &com_len, stdin);
            if (readline == -1)
            {
		free(command_string);  /* Free memory if getline fails */
		command_string = NULL;
		   /* printf("command string freed. program about to exit"); */
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
/*printf("End of main reached. program about to return 0");*/
    return 0;
}

void cleanup(void) {
    /* Free allocated memory */
if ((*command_string_tracker) != NULL){
    free(*command_string_tracker);
    /*printf("Cleanup: Freed unfreed allocated memory.\n");*/
	}
}
void handle_sigint(int signo) {
	(void)signo;
    /*printf("\nCtrl+C received. Program interrupted.\n");*/
    exit(EXIT_FAILURE);
}
