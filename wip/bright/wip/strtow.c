#include "shell.h"

/**
 * wordcount - Counts words in a string based on a delimiter
 * @s: The string to count words from
 * @delimiter: The delimiter character
 *
 * Return: The count of words in the string
 */
int wordcount(char *s, char *delimiter) {
    int i;
    int count = 0;
    int in_word = 0;

    for (i = 0; s[i]; i++) {
        if (_strchr(delimiter, s[i])) {
            if (in_word) {
                in_word = 0;
                count++;
            }
        } else {
            in_word = 1;
        }
    }

    if (in_word) {
        count++;
    }

    return count;
}

/**
 * strtow - Splits a string into an array of words using a delimiter
 * @str: The string to split
 * @delimiter: The delimiter character
 *
 * Return: The array of words, NULL if allocation fails or str is NULL
 */
char **strtow(char *str, char *delimiter) {
    int i, j, k, l, count, m;
    char **word;
    int in_word = 0;

    if (str == NULL || *str == '\0') {
        return NULL;
    }

    count = wordcount(str, delimiter);
    if (count == 1) {
        return NULL;
    }

    word = malloc(count * sizeof(char *));
    if (word == NULL) {
        return NULL;
    }

    word[count - 1] = NULL;
    m = 0;

    for (i = 0; str[i]; i++) {
        if (_strchr(delimiter, str[i])) {
            if (in_word) {
                for (j = 1; str[i + j] != '\0' && !_strchr(delimiter, str[i + j]); j++)
                    ;
                j++;
                word[m] = malloc(j * sizeof(char));
                j--;

                if (word[m] == NULL) {
                    for (k = 0; k < m; k++) {
                        free(word[k]);
                    }

                    free(word[count - 1]);
                    free(word);
                    return NULL;
                }

                for (l = 0; l < j; l++) {
                    word[m][l] = str[i + l];
                }

                word[m][l] = '\0';
                m++;
                i += j;
            }
        } else {
            in_word = 1;
        }
    }

    if (in_word) {
        for (j = 1; str[i + j] != '\0'; j++)
            ;
        j++;
        word[m] = malloc(j * sizeof(char));
        j--;

        if (word[m] == NULL) {
            for (k = 0; k < m; k++) {
                free(word[k]);
            }

            free(word[count - 1]);
            free(word);
            return NULL;
        }

        for (l = 0; l < j; l++) {
            word[m][l] = str[i + l];
        }

        word[m][l] = '\0';
        m++;
    }

    return word;
}
