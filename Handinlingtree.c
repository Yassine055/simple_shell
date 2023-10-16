#include "shell.h"

/**
 * revSrg - Reverses a string
 * @a: Input string
 * Return: void
 */
void revSrg(char *a)
{
	int c = 0, i, j;
	char *st, t;

	while (c >= 0)
	{
		if (a[c] == '\0')
			break;
		c++;
	}
	st = a;

	for (i = 0; i < (c - 1); i++)
	{
		for (j = i + 1; j > 0; j--)
		{
			t = *(st + j);
			*(st + j) = *(st + (j - 1));
			*(st + (j - 1)) = t;
		}
	}
}
