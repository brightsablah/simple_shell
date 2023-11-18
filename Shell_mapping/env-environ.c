#include "main.h"
#include <stdio.h>

extern char **environ;

int main(void)
{
	int len;

	for (len = 0; environ[len] != NULL; len++)
	{
		printf("%s\n", environ[len]);
	}
/*
	printf("My address is : %p\n", (void*)environ);
*/
	return (0);
}
