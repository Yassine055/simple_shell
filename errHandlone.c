#include "shell.h"

/**
 * strCD - Construct error message for cd command
 * @datash: Pointer to DT_SH struct
 * @msg: Message to include in the error
 * @error: Pointer to the error message buffer
 * @ver_str: String representation of the counter
 * Return: Pointer to the constructed error message
 */
char *strCD(DT_SH *datash, char *msg, char *error, char *ver_str)
{
    char *illegal_flag;

    strCPY(error, datash->av[0]);
    strCAT(error, ": ");
    strCAT(error, ver_str);
    strCAT(error, ": ");
    strCAT(error, datash->args[0]);
    strCAT(error, msg);

    if (datash->args[1][0] == '-')
    {
        illegal_flag = malloc(3);
        illegal_flag[0] = '-';
        illegal_flag[1] = datash->args[1][1];
        illegal_flag[2] = '\0';
        strCAT(error, illegal_flag);
        free(illegal_flag);
    }
    else
    {
        strCAT(error, datash->args[1]);
    }

    strCAT(error, "\n");
    strCAT(error, "\0");
    return error;
}

/**
 * errGetCd - Construct error message for cd command
 * @datash: Pointer to DT_SH struct
 * Return: Pointer to the constructed error message
 */
char *errGetCd(DT_SH *datash)
{
    int length, len_id;
    char *error, *ver_str, *msg;

    ver_str = iota(datash->counter);
    if (datash->args[1][0] == '-')
    {
        msg = ": Illegal option ";
        len_id = 2;
    }
    else
    {
        msg = ": can't cd to ";
        len_id = strLEN(datash->args[1]);
    }

    length = strLEN(datash->av[0]) + strLEN(datash->args[0]);
    length += strLEN(ver_str) + strLEN(msg) + len_id + 5;
    error = malloc(sizeof(char) * (length + 1));

    if (error == 0)
    {
        free(ver_str);
        return NULL;
    }

    error = strCAT(datash, msg, error, ver_str);

    free(ver_str);
    return error;
}

/**
 * errNotF - Construct error message for command not found
 * @datash: Pointer to DT_SH struct
 * Return: Pointer to the constructed error message
 */
char *errNotF(DT_SH *datash)
{
    int length;
    char *error, *ver_str;

    ver_str = iota(datash->counter);
    length = strLEN(datash->av[0]) + strLEN(ver_str);
    length += strLEN(datash->args[0]) + 16;
    error = malloc(sizeof(char) * (length + 1));

    if (error == 0)
    {
        free(error);
        free(ver_str);
        return NULL;
    }

    strCPY(error, datash->av[0]);
    strCAT(error, ": ");
    strCAT(error, ver_str);
    strCAT(error, ": ");
    strCAT(error, datash->args[0]);
    strCAT(error, ": not found\n");
    strCAT(error, "\0");
    free(ver_str);
    return error;
}

/**
 * errExitSH - Construct error message for exit command
 * @datash: Pointer to DT_SH struct
 * Return: Pointer to the constructed error message
 */
char *errExitSH(DT_SH *datash)
{
    int length;
    char *error, *ver_str;

    ver_str = iota(datash->counter);
    length = strLEN(datash->av[0]) + strLEN(ver_str);
    length += strLEN(datash->args[0]) + strLEN(datash->args[1]) + 23;
    error = malloc(sizeof(char) * (length + 1));

    if (error == 0)
    {
        free(ver_str);
        return NULL;
    }

    strCPY(error, datash->av[0]);
    strCAT(error, ": ");
    strCAT(error, ver_str);
    strCAT(error, ": ");
    strCAT(error, datash->args[0]);
    strCAT(error, ": Illegal number: ");
    strCAT(error, datash->args[1]);
    strCAT(error, "\n\0");
    free(ver_str);
    return error;
}
