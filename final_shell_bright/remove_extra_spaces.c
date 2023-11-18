#include "shell.h"

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
