#include "shell.h"

/**
 * errEnv -
 * @datash:
 * Return:
 */
char *errEnv(DT_SH *datash)
{
    int length;
    char *error;
    char *ver_str;
    char *msg;

    ver_str = iota(datash->counter);
    msg = ": Unable to add/remove from environment\n";
    length = strLEN(datash->av[0]) + strLEN(ver_str);
    length += strLEN(datash->args[0]) + strLEN(msg) + 4;
    error = malloc(sizeof(char) * (length + 1));
    if (error == 0)
    {
        free(error);
        free(ver_str);
        return (NULL);
    }

    strCPY(error, datash->av[0]);
    strCAT(error, ": ");
    strCAT(error, ver_str);
    strCAT(error, ": ");
    strCAT(error, datash->args[0]);
    strCAT(error, msg);
    strCAT(error, "\0");
    free(ver_str);

    return (error);
}

/**
 * errPath -
 * @datash:
 * Return:
 */
char *errPath(DT_SH *datash)
{
    int length;
    char *ver_str;
    char *error;

    ver_str = iota(datash->counter);
    length = strLEN(datash->av[0]) + strLEN(ver_str);
    length += strLEN(datash->args[0]) + 24;
    error = malloc(sizeof(char) * (length + 1));
    if (error == 0)
    {
        free(error);
        free(ver_str);
        return (NULL);
    }
    strCPY(error, datash->av[0]);
    strCAT(error, ": ");
    strCAT(error, ver_str);
    strCAT(error, ": ");
    strCAT(error, datash->args[0]);
    strCAT(error, ": Permission denied\n");
    strCAT(error, "\0");
    free(ver_str);
    return (error);
}
