#include "main.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    ssize_t readline;
    char *command = NULL;
    size_t command_len = 0;
    int run_command;

    while (1)
    {
	    printf("#mysupershell$ ");

    readline = getline(&command, &command_len, stdin);

    if (readline == -1)
    {
	    printf("\n");
	break;
    }
    else
    {
        if (command[readline - 1] == '\n')
        {
            command[readline - 1] = '\0';
        }

        run_command = system(command);

        if (run_command == -1)
        {
            printf("Failed to execute the command.\n");
        }
    }
    }
    free(command);
    return (0);
}
