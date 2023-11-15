#include "shell.h"

/**
 * wordcount - Counts words in a string based on a delimiter
 * @s: The string to count words from
 * @delimiter: The delimiter character
 *
 * Return: The count of words in the string
 */
int wordcount(char *s, char *delimiter)
{
	int i, count = 0, in_word = 0;

	for (i = 0; s[i]; i++)
	{
		if (_strchr(delimiter, s[i]))
		{
			if (in_word)
			{
				in_word = 0;
				count++;
			}
		} else {
			in_word = 1;
		}
	}
	if (in_word)
	{
		count++;
	}
	return (count);
}

/**
 * strtow - Splits a string into an array of words using a delimiter
 * @str: The string to split
 * @delimiter: The delimiter character
 *
 * Return: The array of words, NULL if allocation fails or str is NULL
 */
char **strtow(char *str, char *delimiter)
{
    int i, j, k, l, count, m, in_word = 0;
    char **word;

    if (str == NULL || *str == '\0')
        return NULL;

    count = wordcount(str, delimiter);
    if (count <= 0) 
        return NULL;

    word = malloc(count * sizeof(char *));
    if (word == NULL)
        return NULL;

    word[count - 1] = NULL;
    m = 0;

    for (i = 0; str[i]; i++)
    {
        if (_strchr(delimiter, str[i]))
        {
            if (in_word)
            {
                for (j = 1; str[i + j] != '\0' && !_strchr(delimiter, str[i + j]); j++)
                    ;
                word[m] = malloc((j + 1) * sizeof(char));
                if (word[m] == NULL)
                {
                    for (k = 0; k < m; k++)
                    {
                        free(word[k]);
                    }
                    free(word);
                    return NULL;
                }
                for (l = 0; l < j; l++)
                {
                    word[m][l] = str[i + l];
                }
                word[m][l] = '\0';
                m++;
                i += j - 1;
            }
            in_word = 0;
        }
        else
        {
            in_word = 1;
        }
    }

    if (in_word)
    {
        j = strlen(&str[i]); 
        word[m] = malloc((j + 1) * sizeof(char));
        if (word[m] == NULL)
        {
            for (k = 0; k < m; k++)
            {
                free(word[k]);
            }
            free(word);
            return NULL;
        }
        for (l = 0; l < j; l++)
        {
            word[m][l] = str[i + l];
        }
        word[m][l] = '\0';
        m++;
    }

    return word;
}
