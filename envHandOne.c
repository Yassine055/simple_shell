#include "shell.h"

/**
 * cmpEnvName - Compares the name of an environment variable
 * @nenv: Environment variable
 * @name: Name to compare
 *
 * Return: Number of characters matching the name
 */
int cmpEnvName(const char *nenv, const char *name)
{
	int i;

	for (i = 0; nenv[i] != '='; i++)
	{
		if (nenv[i] != name[i])
		{
			return (0);
		}
	}

	return (i + 1);
}

/**
 * getenv - Gets the value of an environment variable
 * @name: Name of the environment variable
 * @_environ: Array of environment variables
 *
 * Return: Value of the environment variable
 */
char *getenv(const char *name, char **_environ)
{
	char *ptr_env;
	int i, mov;

	/* Init ptr_env val */
	ptr_env = NULL;
	mov = 0;
	/* */
	/*  */
	for (i = 0; _environ[i]; i++)
	{
		/* comments here */
		mov = cmpEnvName(_environ[i], name);
		if (mov)
		{
			ptr_env = _environ[i];
			break;
		}
	}

	return (ptr_env + mov);
}

/**
 * eNV - Prints the environment variables
 * @datash: Shell data
 *
 * Return: 1 on success
 */
int eNV(DT_SH *datash)
{
	int i, j;

	for (i = 0; datash->_environ[i]; i++)
	{
		for (j = 0; datash->_environ[i][j]; j++)
			;

		write(STDOUT_FILENO, datash->_environ[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	datash->status = 0;

	return (1);
}
