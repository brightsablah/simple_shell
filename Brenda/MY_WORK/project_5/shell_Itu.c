#include "shell.h"

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

/**
 * exit_shell - Exits the shell if the command is "exit"
 * @command_string: The command string
 *
 * Return: None
 */
void exit_shell(char *command_string)
{
	if (_strcmp(command_string, "exit") == 0)
	{
		exit(0);
	}
}

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

	if (isatty(STDIN_FILENO))
	{
		while (1)
		{
			print_prompt();
			readline = getline(&command_string, &com_len, stdin);
			if (readline == -1)
			{
				exit_shell(NULL);
				break;
			}
			if (readline > 1)
			{
				if (command_string[readline - 1] == '\n')
					command_string[readline - 1] = '\0';

				if (_strcmp(command_string, "exit") == 0)
				{
					exit_shell(command_string);
					break;
				} else
				{
					execute_command(command_string);
				}
			}
		}
		free(command_string);
	} else
	{
		if (argc > 1)
		{
			script = fopen(argv[1], "r");
			if (script != NULL)
			{
				nonInteractiveMode(script);
				fclose(script);
			} else
			{
				return (1);
			}
		} else
		{
			executePipedCommands();
		}
	}
	return (0);
}
