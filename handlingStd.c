#include "shell.h"

/**
 * getLen - calculates the length of an integer
 * @n: input integer
 * Return: length of the integer
 */
int getLen(int n)
{
	unsigned int n1;
	int length = 1;

	if (n < 0)
	{
		length++;
		n1 = n * -1;
	}
	else
	{
		n1 = n;
	}
	while (n1 > 9)
	{
		length++;
		n1 = n1 / 10;
	}

	return (length);
}

/**
 * aIt - converts an integer to a string
 * @n: input integer
 * Return: string representation of the integer
 */
char *aIt(int n)
{
	unsigned int n1;
	int length = getLen(n);
	char *buffer;

	buffer = malloc(sizeof(char) * (length + 1));
	if (buffer == 0)
		return (NULL);

	*(buffer + length) = '\0';

	if (n < 0)
	{
		n1 = n * -1;
		buffer[0] = '-';
	}
	else
	{
		n1 = n;
	}

	length--;
	do {
		*(buffer + length) = (n1 % 10) + '0';
		n1 = n1 / 10;
		length--;
	} while (n1 > 0);

	return (buffer);
}

/**
 * iota - converts a string to an integer
 * @s: input string
 * Return: converted integer
 */
int iota(char *s)
{
	unsigned int count = 0, size = 0, oi = 0, pn = 1, m = 1, i;

	while (*(s + count) != '\0')
	{
		if (size > 0 && (*(s + count) < '0' || *(s + count) > '9'))
			break;

		if (*(s + count) == '-')
			pn *= -1;

		if ((*(s + count) >= '0') && (*(s + count) <= '9'))
		{
			if (size > 0)
				m *= 10;
			size++;
		}
		count++;
	}

	for (i = count - size; i < count; i++)
	{
		oi = oi + ((*(s + i) - 48) * m);
		m /= 10;
	}
	return (oi * pn);
}
