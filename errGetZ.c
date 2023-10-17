#include "shell.h"

/**
 * getErr - Get error message based on evaluation value
 * @datash: Pointer to DT_SH struct
 * @eval: Evaluation value
 * Return: Evaluation value
 */
int getErr(DT_SH *datash, int eval)
{
    char *error;

    switch (eval)
    {
    case -1:
        error = errEnv(datash);
        break;
    case 126:
        error = errPath(datash);
        break;
    case 127:
        error = errNotF(datash);
        break;
    case 2:
        if (strCMP("exit", datash->args[0]) == 0)
            error = errExitSH(datash);
        else if (strCMP("cd", datash->args[0]) == 0)
            error = errGetCd(datash);
        break;
    }

    // Print the error message and free the allocated memory
    if (error)
    {
        write(STDERR_FILENO, error, strLEN(error));
        free(error);
    }

    datash->status = eval;
    return eval;
}
