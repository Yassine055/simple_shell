#include "shell.h"

/**
 * strDUP - Duplicates a string.
 * @s: The source string.
 *
 * Return: A pointer to the duplicated string.
 */

char *strDUP(const char *s)
{
	char *new;
	size_t len;

	len = strLEN(s);
	new = malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	mC(new, s, len + 1);
	return (new);
}

/**
 * strLEN - Calculates the length of a string.
 * @s: The input string.
 *
 * Return: The length of the string.
 */

int strLEN(const char *s)
{
	int l;

	for (l = 0; s[l] != 0; l++)
	{
	}
	return (l);
}

/**
 * cmpCHars - Compares characters in a string with a delimiter.
 * @str: The string to compare.
 * @delim: The delimiter string.
 *
 * Return: 1 if all characters in the string match the delimiter, 0 otherwise.
 */

int cmpCHars(char str[], const char *delim)
{
	unsigned int i, j, k;

	for (i = 0, k = 0; str[i]; i++)
	{
		for (j = 0; delim[j]; j++)
		{
			if (str[i] == delim[j])
			{
				k++;
				break;
			}
		}
	}
	if (i == k)
		return (1);
	return (0);
}

/**
 * strT - Tokenizes a string using a delimiter.
 * @str: The string to tokenize.
 * @delim: The delimiter string.
 *
 * Return: A pointer to the next token in the string.
 */

char *strT(char str[], const char *delim)
{
	static char *splitted, *str_end;
	char *str_start;
	unsigned int i, bool;

	if (str != NULL)
	{
		if (cmpCH(str, delim))
			return (NULL);
		splitted = str;
		i = strLEN(str);
		str_end = &str[i];
	}
	str_start = splitted;
	if (str_start == str_end)
		return (NULL);

	for (bool = 0; *splitted; splitted++)
	{
		if (splitted != str_start)
			if (*splitted && *(splitted - 1) == '\0')
				break;

		for (i = 0; delim[i]; i++)
		{
			if (*splitted == delim[i])
			{
				*splitted = '\0';
				if (splitted == str_start)
					str_start++;
				break;
			}
		}
		if (bool == 0 && *splitted)
			bool = 1;
	}
	if (bool == 0)
		return (NULL);
	return (str_start);
}

/**
 * isDigit - Checks if a string contains only digits.
 * @s: The input string.
 *
 * Return: 1 if the string contains only digits, 0 otherwise.
 */

int isDigit(const char *s)
{
	unsigned int i;

	for (i = 0; s[i]; i++)
	{
		if (s[i] < 48 || s[i] > 57)
			return (0);
	}
	return (1);
}
