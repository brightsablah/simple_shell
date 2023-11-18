#include "shell.h"

/**
 * change_directory - Change the current working directory
 * @arguments: Arguments for the cd command
 */
void change_directory(char **arguments)
{
	const char *home_directory = _getenv("HOME");
    if (arguments[1] == NULL)
    {
	    if (home_directory == NULL)
		    return;

	    if (chdir(home_directory) == -1)
		    perror("cd");
    }
    else
    {
        if (strcmp(arguments[1], "/") == 0)
        {
		if (chdir("/") == -1)
		    perror("cd");
        }
        else
        {
            if (chdir(arguments[1]) == -1)
            {
                perror("cd");
            }
        }
    }
}
