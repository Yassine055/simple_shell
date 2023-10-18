#include "shell.h"

/**
 * getB - Gets the corresponding builtin function for a given command
 * @cmd: Command string
 * Return: Function pointer to the corresponding builtin function
 */
int (*getB(char *cmd))(DT_SH *)
{
	builtin_t builtin[] = {
		{"env", eNV},
		{"exit", exitSH},
		{"setenv", setENV},
		{"unsetenv", unSetEnv},
		{"cd", cdSHell},
		{"help", hEllP},
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
