#include "shell.h"

void exit_shell(char **arguments)
{
    int status = 0;

    if (arguments != NULL && arguments[1] != NULL)
    {
        status = _atoi(arguments[1]);
    }

    exit(status);
}
