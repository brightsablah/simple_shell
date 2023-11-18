#include "main.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	ssize_t readline;
	char *command = NULL;
	size_t command_len = 0;

	printf("$ ");

	readline = getline(&command, &command_len, stdin);

	if (readline == -1)
	{
		printf("EOF\n");
	}
	else
	{
		printf("%s", command);
	}

	free(command);
	return (0);
}
