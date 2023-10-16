#include "shell.h"

/**
 * cdDot - Handles the cd command with "." argument
 * @datash: Shell data
 * Return: void
 */
void cdDot(DT_SH *datash)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = strDUP(pwd);
	setENV("OLDPWD", cp_pwd, datash);
	dir = datash->args[1];
	if (strCMP(".", dir) == 0)
	{
		setENV("PWD", cp_pwd, datash);
		free(cp_pwd);
		return;
	}
	if (strCMP("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cp_strtok_pwd = cp_pwd;
	revSrg(cp_strtok_pwd);
	cp_strtok_pwd = strT(cp_strtok_pwd, "/");
	if (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = strT(NULL, "\0");

		if (cp_strtok_pwd != NULL)
			revSrg(cp_strtok_pwd);
	}
	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd);
		setENV("PWD", cp_strtok_pwd, datash);
	}
	else
	{
		chdir("/");
		setENV("PWD", "/", datash);
	}
	datash->status = 0;
	free(cp_pwd);
}

/**
 * cdTo - Handles the cd command with a specified directory
 * @datash: Shell data
 * Return: void
 */
void cdTo(DT_SH *datash)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));
	dir = datash->args[1];
	if (chdir(dir) == -1)
	{
		getErr(datash, 2);
		return;
	}
	cp_pwd = strDUP(pwd);
	setENV("OLDPWD", cp_pwd, datash);
	cp_dir = strDUP(dir);
	setENV("PWD", cp_dir, datash);
	free(cp_pwd);
	free(cp_dir);
	datash->status = 0;
	chdir(dir);
}

/**
 * cdPrevious - Handles the cd command to go to the previous directory
 * @datash: Shell data
 * Return: void
 */
void cdPrevious(DT_SH *datash)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = getd(pwd);
	p_oldpwd = getENV("OLDPWD", datash->_environ);
	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = strDUP(p_oldpwd);
	setENV("OLDPWD", cp_pwd, datash);
	if (chdir(cp_oldpwd) == -1)
		setENV("PWD", cp_pwd, datash);
	else
		setENV("PWD", cp_oldpwd, datash);
	p_pwd = getENV("PWD", datash->_environ);
	write(STDOUT_FILENO, p_pwd, strLEN(p_pwd));
	write(STDOUT_FILENO, "\n", 1);
	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);
	datash->status = 0;
	chdir(p_pwd);
}

/**
 * cdToHome - Handles the cd command to go to the home directory
 * @datash: Shell data
 * Return: void
 */
void cdToHome(DT_SH *datash)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = strDUP(pwd);
	home = getENV("HOME", datash->_environ);
	if (home == NULL)
	{
		setENV("OLDPWD", p_pwd, datash);
		free(p_pwd);
		return;
	}
	if (chdir(home) == -1)
	{
		getErr(datash, 2);
		free(p_pwd);
		return;
	}
	setENV("OLDPWD", p_pwd, datash);
	setENV("PWD", home, datash);
	free(p_pwd);
	datash->status = 0;
}
