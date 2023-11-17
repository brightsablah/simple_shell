#include "shell.h"

/**
 * strtow - Splits a string into an array of words using a delimiter
 * @str: The string to split
 * @delimiter: The delimiter character
 *
 * Return: The array of words, NULL if allocation fails or str is NULL
 */
char **strtow(char *str, char *delimiter)
{
	int i, j, m, k;
    int in_word = 0;
    int count = 0;
    
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

                
                word[m] = _strdup(&str[i]);
                if (word[m] == NULL)
                {
                  
                    for (k = 0; k < m; k++)
                        free(word[k]);
                    free(word);
                    return NULL;
                }

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
        word[m] = _strdup(&str[i]);
        if (word[m] == NULL)
        {
            
            for (k = 0; k < m; k++)
                free(word[k]);
            free(word);
            return NULL;
        }

        m++;
    }

    return word;
}
