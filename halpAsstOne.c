#include "shell.h"


/**
 * hEllP -
 * @datash:
 * Return:
*/
int hEllP(DT_SH *datash)
{


    if (datash->args[1] == 0)
        helpG();
    else if (strCMP(datash->args[1], "setenv") == 0)
        helpSTenv();
    else if (strCMP(datash->args[1], "env") == 0)
        helpENV();
    else if (strCMP(datash->args[1], "unsetenv") == 0)
        helpUNSenv();
    else if (strCMP(datash->args[1], "help") == 0)
        help();
    else if (strCMP(datash->args[1], "exit") == 0)
        helpEX();
    else if (strCMP(datash->args[1], "cd") == 0)
        helpCD();
    else if (strCMP(datash->args[1], "alias") == 0)
        helpAL();
    else
        write(STDERR_FILENO, datash->args[0],
              strLEN(datash->args[0]));


    datash->status = 0;
    return (1);
}
