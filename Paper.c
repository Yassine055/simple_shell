#include "shell.h"

/**
 * swapCHar - Swaps special characters in the input string.
 * @input: The input string.
 * @bool: If 0, replace special characters; if 1, restore original characters.
 * Return: Modified input string.
 */
char *swapCHar(char *input, int bool)
{
	int i;

	if (bool == 0)
	{
		for (i = 0; input[i]; i++)
		{
			if (input[i] == '|')
			{
				if (input[i + 1] != '|')
					input[i] = 16;
				else
					i++;
			}

			if (input[i] == '&')
			{
				if (input[i + 1] != '&')
					input[i] = 12;
				else
					i++;
			}
		}
	}
	else
	{
		for (i = 0; input[i]; i++)
		{
			input[i] = (input[i] == 16 ? '|' : input[i]);
			input[i] = (input[i] == 12 ? '&' : input[i]);
		}
	}
	return (input);
}

/**
 * addNodes - Adds nodes to the separator list and line list.
 * @head_s: Head of the separator list.
 * @head_l: Head of the line list.
 * @input: Input string.
 * Return: void
 */
void addNodes(sList **head_s, lList **head_l, char *input)
{
	int i;
	char *line;

	input = swapCHar(input, 0);

	for (i = 0; input[i]; i++)
	{
		if (input[i] == ';')
			addSNEnd(head_s, input[i]);

		if (input[i] == '|' || input[i] == '&')
		{
			addSNEnd(head_s, input[i]);
			i++;
		}
	}

	line = _strtok(input, ";|&");
	do {
		line = swapCHar(line, 1);
		addLNEnd(head_l, line);
		line = strT(NULL, ";|&");
	} while (line != NULL);
}

/**
 * Next - Moves to the next separator and line.
 * @list_s: Separator list.
 * @list_l: Line list.
 * @datash: Data structure.
 * Return: void
 */
void Next(sList **list_s, lList **list_l, DT_SH *datash)
{
	int loop_sep;
	sList *ls_s;
	lList *ls_l;

	loop_sep = 1;
	ls_s = *list_s;
	ls_l = *list_l;

	while (ls_s != NULL && loop_sep)
	{
		if (datash->status == 0)
		{
			if (ls_s->separator == '&' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->separator == '|' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->next;
	}

	*list_s = ls_s;
	*list_l = ls_l;
}

/**
 * spComm - Parses and executes commands.
 * @datash: Data structure.
 * @input: Input string.
 * Return: 0 if successful, 1 otherwise.
 */
int spComm(DT_SH *datash, char *input)
{
	sList *head_s, *list_s;
	lList *head_l, *list_l;
	int loop;

	head_s = NULL;
	head_l = NULL;

	addNodes(&head_s, &head_l, input);

	list_s = head_s;
	list_l = head_l;

	while (list_l != NULL)
	{
		datash->input = list_l->line;
		datash->args = spLine(datash->input);
		loop = exeLine(datash);
		free(datash->args);

		if (loop == 0)
			break;

		Next(&list_s, &list_l, datash);

		if (list_l != NULL)
			list_l = list_l->next;
	}

	freeSList(&head_s);
	freeLList(&head_l);

	if (loop == 0)
		return (0);
	return (1);
}

/**
 * spLine - Splits an input string into tokens.
 * @input: Input string.
 * Return: Array of tokens.
 */
char **spLine(char *input)
{
	size_t bsize;
	size_t i;
	char **tokens;
	char *token;

	bsize = TOK_BUFSIZE;
	tokens = malloc(sizeof(char *) * (bsize));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = strT(input, TOK_DELIM);
	tokens[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == bsize)
		{
			bsize += TOK_BUFSIZE;
			tokens = rCDP(tokens, i, sizeof(char *) * bsize);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = strT(NULL, TOK_DELIM);
		tokens[i] = token;
	}

	return (tokens);
}
