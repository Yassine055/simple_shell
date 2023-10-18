#include "shell.h"

/**
 * exeLine -
 * @datash:
 * Return:
 */
int exeLine(DT_SH *datash)
{
    int (*builtin)(DT_SH *datash);

    if (datash->args[0] == NULL)
        return (1);

    builtin = getB(datash->args[0]);

    if (builtin != NULL)
        return (builtin(datash));

    return (cmdEX(datash));
}
