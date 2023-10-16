#include "shell.h"

/**
 * cdSHell - Handles the cd command in the shell
 * @datash: Shell data
 * Return: 1 on success, 0 on failure
 */
int cdSHell(DT_SH *datash)
{
	char *dir;
	int ishome, ishome2, isddash;

	dir = datash->args[1];

	if (dir != NULL)
	{
		ishome = strCMP("$HOME", dir);
		ishome2 = strCMP("~", dir);
		isddash = strCMP("--", dir);
	}

	if (dir == NULL || !ishome || !ishome2 || !isddash)
	{
		cdToHome(datash);
		return (1);
	}

	if (strCMP("-", dir) == 0)
	{
		cdPrevious(datash);
		return (1);
	}

	if (strCMP(".", dir) == 0 || strCMP("..", dir) == 0)
	{
		cdDot(datash);
		return (1);
	}

	cdTo(datash);

	return (1);
}
