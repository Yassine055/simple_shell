#include "shell.h"

/**
 * getB - Gets the corresponding builtin function for a given command
 * @cmd: Command string
 * Return: Function pointer to the corresponding builtin function
 */
int (*getB(char *cmd))(DT_SH *)
{
	builtin_t builtin[] = {
		{"env", _env},
		{"exit", exit_shell},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{"cd", cd_shell},
		{"help", get_help},
		{NULL, NULL}
	};
	int i;

	for (i = 0; builtin[i].name; i++)
	{
		if (strCMP(builtin[i].name, cmd) == 0)
			break;
	}
	return (builtin[i].f);
}
