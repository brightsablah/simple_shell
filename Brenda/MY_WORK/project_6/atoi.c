#include "shell.h"

/**
 * _atoi - convert a string to an integer
 * @s: string
 *
 * Return: converted integer
 */
int _atoi(char *s)
{
    int sign = 1;
    int num = 0;

    while (*s == ' ' || (*s >= '\t' && *s <= '\r'))
        s++;

    if (*s == '-' || *s == '+') {
        sign = (*s == '-') ? -1 : 1;
        s++;
    }

    while (*s >= '0' && *s <= '9') {
        num = (num * 10) + (*s - '0');
        s++;
    }

    return num * sign;
}
