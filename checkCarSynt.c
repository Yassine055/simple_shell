#include "shell.h"

/**
 * repeatEDCHar - Counts repeated characters in a string
 * @input: Input string
 * @i: Current index
 * Return: Number of repeated characters
 */
int repeatEDCHar(char *input, int i)
{
	if (*(input - 1) == *input)
		return (repeatEDCHar(input - 1, i + 1));

	return (i);
}

/**
 * errSO - Checks for syntax errors in the command
 * @input: Input string
 * @i: Current index
 * @last: Last character processed
 * Return: Index of the syntax error or 0 if none
 */
int errSO(char *input, int i, char last)
{
	int count;

	count = 0;
	if (*input == '\0')
		return (0);

	if (*input == ' ' || *input == '\t')
		return (errSO(input + 1, i + 1, last));

	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
			return (i);

	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (i);

		if (last == '|')
		{
			count = repeatEDCHar(input, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return (i);

		if (last == '&')
		{
			count = repeatEDCHar(input, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	return (errSO(input + 1, i + 1, *input));
}

/**
 * firstCH - Finds the first non-space character in the input
 * @input: Input string
 * @i: Index of the first non-space character
 * Return: 0 if successful, -1 if there is a syntax error
 */
int firstCH(char *input, int *i)
{
	for (*i = 0; input[*i]; *i += 1)
	{
		if (input[*i] == ' ' || input[*i] == '\t')
			continue;

		if (input[*i] == ';' || input[*i] == '|' || input[*i] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * pSyErr - Prints a syntax error message to STDERR
 * @datash: Shell data
 * @input: Input string
 * @i: Index of the syntax error
 * @bool: Boolean flag
 * Return: void
 */
void pSyErr(DT_SH *datash, char *input, int i, int bool)
{
	char *msg, *msg2, *msg3, *error, *counter;
	int length;

	if (input[i] == ';')
	{
		msg = (input[i + 1] == ';' ? ";;" : ";");
	}
	if (input[i] == '|')
		msg = (input[i + 1] == '|' ? "||" : "|");
	if (input[i] == '&')
		msg = (input[i + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax error: \"";
	msg3 = "\"unexpected\n";
	counter = aIt(datash->counter);
	length = strLEN(datash->av[0]) + strLEN(counter);
	length += strLEN(msg) + strLEN(msg2) + strLEN(msg3) + 2;

	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(counter);
		return;
	}
	strCAY(error, datash->av[0]);
	strCAT(error, ": ");
	strCAT(error, counter);
	strCAT(error, msg2);
	strCAT(error, msg);
	strCAT(error, msg3);
	strCAT(error, "\0");

	write(STDERR_FILENO, error, length);
	free(error);
	free(counter);
}

/**
 * chSyErr - Checks for syntax errors in the command
 * @datash: Shell data
 * @input: Input string
 * Return: 1 if there is a syntax error, 0 otherwise
 */
int chSyErr(data_shell *datash, char *input)
{
	int begin = 0;
	int f_char = 0;
	int i = 0;

	f_char = firstCH(input, &begin);
	if (f_char == -1)
	{
		pSyErr(datash, input, begin, 0);
		return (1);
	}

	i = errSO(input + begin, 0, *(input + begin));
	if (i != 0)
	{
		pSyErr(datash, input, begin + i, 1);
		return (1);
	}

	return (0);
}
