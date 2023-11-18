#include "main.h"
#include <stdio.h>
#include <unistd.h>

/**
 * ppid - parent process identification
 */
int main(void)
{
	pid_t my_ppid;

	my_ppid = getppid();
	printf("%u\n", my_ppid);

	return (0);
}
