#include "main.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    char *default_argv[] = {"/bin/ls", "-l", NULL};
    char **new_argv = default_argv;
    int num = 5;
    int count;
    pid_t child_pid;

    for (count = 0; count < num; count++)
    {
        child_pid = fork();

        if (child_pid == -1)
        {
            perror("Error forking");
            return (1);
        }
        if (child_pid == 0)
        {
            if (argc == 2)
            {
                new_argv = (char *[]){"/bin/ls", "-l", argv[1], NULL};
            }

            if (execve(new_argv[0], new_argv, NULL) == -1)
            {
                perror("Error:");
                return (1);
            }
        }
        else
        {
            wait(NULL);
        }
    }
    return (0);
}
