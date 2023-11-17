#include "shell.h"


/**
 * is_executable - Checks if a file is executable
 * @path: file path
 *
 * Return: 1 for executable, otherwise 0
 */
int is_executable(const char *path)
{
	struct stat st;

	if (path == NULL || *path == '\0')
		return (0);

	if (stat(path, &st) == 0)
	{
		if (S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR))
			return (1);
        }

	return(0);
}

