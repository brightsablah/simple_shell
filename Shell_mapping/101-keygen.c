#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/**
 * main - Entry point
 * generate random valid passwords for the programme 101-crackme
 *
 * Return: random password
 */
int main(void)
{
	char str[100];
	int i = 0;
	int num = 0;
	int sum = 0;

	srand(time(NULL));

	for (i = 0; sum <= 2644; i++)
	{
		num = (rand() % 25) +65;

		str[i] = num;
		sum = sum + num;
	}

	str[i++] = 2772 - sum;
	str[i++] = '\0';

	printf("%s\n", str);

	return (0);

}
