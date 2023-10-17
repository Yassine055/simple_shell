#include "shell.h"

/**
 * cPInfo - Create a new environment variable string
 * @name: Name of the environment variable
 * @value: Value of the environment variable
 *
 * Return: A new string in the format "name=value\0"
 */
char *cPInfo(char *name, char *value)
{
    char *new;
    int len_name, len_value, len;

    len_name = strLEN(name);
    len_value = strLEN(value);
    len = len_name + len_value + 2;

    new = malloc(sizeof(char) * len);
    strCPY(new, name);
    strCAT(new, "=");
    strCAT(new, value);
    strCAT(new, "\0");

    return new;
}

/**
 * setENV - Set an environment variable or update its value
 * @name: Name of the environment variable
 * @value: Value to set for the environment variable
 * @datash: Shell data structure
 *
 * Return: None
 */
void setENV(char *name, char *value, DT_SH *datash)
{
    int i;
    char *var_env, *name_env;

    for (i = 0; datash->_environ[i]; i++)
    {
        var_env = strDUP(datash->_environ[i]);
        name_env = strT(var_env, "=");

        if (_strcmp(name_env, name) == 0)
        {
            free(datash->_environ[i]);
            datash->_environ[i] = cPInfo(name_env, value);
            free(var_env);
            return;
        }

        free(var_env);
    }

    datash->_environ = _reallocdp(datash->_environ, i, sizeof(char *) * (i + 2));
    datash->_environ[i] = cPInfo(name, value);
    datash->_environ[i + 1] = NULL;
}

/**
 * setEnvCommand - Handle the setenv command
 * @datash: Shell data structure
 *
 * Return: 1 on success, 0 on failure
 */
int setEnvCommand(DT_SH *datash)
{
    if (datash->args[1] == NULL || datash->args[2] == NULL)
    {
        getErr(datash, -1);
        return 1;
    }

    setENV(datash->args[1], datash->args[2], datash);

    return 1;
}

/**
 * unSetEnv - Unset an environment variable
 * @datash: Shell data structure
 *
 * Return: 1 on success, 0 on failure
 */
int unSetEnv(DT_SH *datash)
{
    char **realloc_environ;
    char *var_env, *name_env;
    int i, j, k;

    if (datash->args[1] == NULL)
    {
        getErr(datash, -1);
        return 1;
    }

    k = -1;
    for (i = 0; datash->_environ[i]; i++)
    {
        var_env = strDUP(datash->_environ[i]);
        name_env = strT(var_env, "=");

        if (strCMP(name_env, datash->args[1]) == 0)
        {
            k = i;
        }

        free(var_env);
    }

    if (k == -1)
    {
        getErr(datash, -1);
        return 1;
    }

    realloc_environ = malloc(sizeof(char *) * i);

    for (i = j = 0; datash->_environ[i]; i++)
    {
        if (i != k)
        {
            realloc_environ[j] = datash->_environ[i];
            j++;
        }
    }

    realloc_environ[j] = NULL;

    free(datash->_environ[k]);
    free(datash->_environ);

    datash->_environ = realloc_environ;

    return 1;
}
