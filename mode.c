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

/**
 * is_whitespace - checks for spaces
 * @str: character to check
 *
 * Return: 1 for space character , otherwise 0
 */
int is_whitespace(const char ch)
{
	return (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r');
}

/**
 * remove_extra_spaces - remove tailing whitespaces
 * line: line to remove tailing spaces from
 *
 * Return : pointer to cleanerd line
 */
char* remove_extra_spaces(const char* line)
{
	int i, j, space_flag;
	char* cleaned_line;

	if (line == NULL || *line == '\0')
		return (NULL);

	cleaned_line = malloc(strlen(line) + 1);
	if (cleaned_line == NULL)
		return (NULL);

	space_flag = 0;

	for (i = 0, j = 0; line[i] != '\0'; i++)
	{
		if (line[i] != ' ')
		{
			cleaned_line[j++] = line[i];
			space_flag = 0;
		}
		else
		{
			if (space_flag == 0)
			{
				cleaned_line[j++] = line[i];
			}
			space_flag = 1;
		}
	}

	cleaned_line[j] = '\0';
	return (cleaned_line);
}


/**
 * nonInteractiveMode - Executes commands in non interacting mode
 * @script: The file to read commands from
 *
 * Return: None
 */
void nonInteractiveMode(FILE *script) {
	char *line = NULL, *cleaned_line;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, script)) != -1) {

        if (read > 1) {
            if (line[read - 1] == '\n') {
                line[read - 1] = '\0';
            }
            cleaned_line = remove_extra_spaces(line);
            if (cleaned_line != NULL) {
               if (is_executable(cleaned_line)) {
                    execute_command(cleaned_line);
                }
                free(cleaned_line);
            }
        }
    }
    free(line);
}
