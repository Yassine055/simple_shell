#include "shell.h"

/**
 * help -
 * Return:
 */
void help(void)
{
    char *help = "help: help [-dms] [pattern ...]\n";

    write(STDOUT_FILENO, help, strLEN(help));
    help = "\tDisplay information about builtin commands.\n ";
    write(STDOUT_FILENO, help, strLEN(help));
    help = "Displays brief summaries of builtin commands.\n";
    write(STDOUT_FILENO, help, strLEN(help));
}

/**
 * helpAL -
 * Return:
 */
void helpAL(void)
{
    char *help = "alias: alias [-p] [name[=value]...]\n";

    write(STDOUT_FILENO, help, strLEN(help));
    help = "\tDefine or display aliases.\n ";
    write(STDOUT_FILENO, help, strLEN(help));
}

/**
 * helpCD -
 * Return:
 */
void helpCD(void)
{
    char *help = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

    write(STDOUT_FILENO, help, strLEN(help));
    help = "\tChange the shell working directory.\n ";
    write(STDOUT_FILENO, help, strLEN(help));
}
