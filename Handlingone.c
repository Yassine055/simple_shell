#include "shell.h"


/**
 * strCAT - Concatenate two strings
 * @dest: Destination string
 * @src: Source string
 *
 * Return: Pointer to the concatenated string (dest)
 */

char *strCAT(char *dest, const char *src)
{
	int i;
	int j;


	for (i = 0; dest[i] != '\0'; i++)
		;


	for (j = 0; src[j] != '\0'; j++)
	{
		dest[i] = src[j];
		i++;
	}

	dest[i] = '\0';
	return (dest);
}
/**
 * strCPY - Copy a string
 * @dest: Destination string
 * @src: Source string
 * Return: Pointer to the copied string (dest)
 */

char *strCPY(char *dest, char *src)
{
	size_t a;


	for (a = 0; src[a] != '\0'; a++)
	{
		dest[a] = src[a];
	}
	dest[a] = '\0';


	return (dest);
}
/**
 * strCMP - Compare two strings
 * @s1: First string
 * @s2: Second string
 * Return: 0 if equal, positive if s1 > s2, negative if s1 < s2
 */

int strCMP(char *s1, char *s2)
{
	int i;


	for (i = 0; s1[i] == s2[i] && s1[i]; i++)
		;


	if (s1[i] > s2[i])
		return (1);
	if (s1[i] < s2[i])
		return (-1);
	return (0);
}
/**
 * strCHR - Locate character in a string
 * @s: Target string
 * @c: Character to locate
 * Return: Pointer to the first occurrence of the character in the string,
 * or NULL if the character is not found
 */

char *strCHR(char *s, char c)
{
	unsigned int i = 0;


	for (; *(s + i) != '\0'; i++)
		if (*(s + i) == c)
			return (s + i);
	if (*(s + i) == c)
		return (s + i);
	return ('\0');
}
/**
 * strSPN - Get the length of a prefix substring
 * @s: String to check
 * @accept: Set of characters to accept
 * Return: Number of bytes in the initial segment of s which consist only of
 * bytes from accept
 */

int strSPN(char *s, char *accept)
{
	int i, j, bool;


	for (i = 0; *(s + i) != '\0'; i++)
	{
	bool = 1;
	for (j = 0; *(accept + j) != '\0'; j++)
	{
		if (*(s + i) == *(accept + j))
		{
			bool = 0;
			break;
		}
	}
	if (bool == 1)
	break;
	}
		return (i);
}
