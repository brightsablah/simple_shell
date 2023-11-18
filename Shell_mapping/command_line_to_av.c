#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 128

char *_strstr(char *haystack, char *needle);
char *_strncpy(char *dest, char *src, int n);

int main(int argc, char *argv[])
{
    char *delimiter = " ";
    char *word;
    char buffer[MAX_LEN];
    int count = 0;

    if (argc != 2)
    {
        printf("Error\n");
        return (1);
    }

    _strncpy(buffer, argv[1], MAX_LEN);

    while (count < MAX_LEN && (word = _strstr(buffer, delimiter)) != NULL)
    {
        *word = '\0';
        printf("%s\n",buffer);
        buffer[0] = '\0';
	_strncpy(buffer, word + 1, MAX_LEN);
        count++;
    }

    if (buffer[0] != '\0' && count < MAX_LEN)
    {
        printf("%s\n", buffer);
        count++;
    }

    return (0);
}

char *_strstr(char *haystack, char *needle)
{
    char *start;
    char *sub;

    while (*haystack != '\0')
    {
        start = haystack;
        sub = needle;

        while (*sub == *haystack && *haystack != 0 && *sub != 0)
        {
            haystack++;
            sub++;
        }
        if (*sub == 0)
            return start;
        haystack = start + 1;
    }
    return (NULL);
}

char *_strncpy(char *dest, char *src, int n)
{
    int i = 0, len = 0;

    while (src[i++])
        len++;

    for (i = 0; i < n && src[i]; i++)
        dest[i] = src[i];

    for (i = len; n > i; i++)
        dest[i] = '\0';

    return (dest);
}
