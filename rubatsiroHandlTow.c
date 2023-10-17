#include "shell.h"

/**
 * helpENV - Display help information for env command
 * Return: None
 */
void helpENV(void)
{
    char *help = "env: env [option] [name=value] [command [args]]\n\t";

    write(STDOUT_FILENO, help, strLEN(help));
    help = "Print the environment of the shell.\n";
    write(STDOUT_FILENO, help, strLEN(help));
}

/**
 * helpSTenv - Display help information for setenv command
 * Return: None
 */
void helpSTenv(void)
{
    char *help = "setenv: setenv (const char *name, const char *value, int replace)\n\t";

    write(STDOUT_FILENO, help, strLEN(help));
    help = "Add a new definition to the environment\n";
    write(STDOUT_FILENO, help, strLEN(help));
}

/**
 * helpUNSenv - Display help information for unsetenv command
 * Return: None
 */
void helpUNSenv(void)
{
    char *help = "unsetenv: unsetenv (const char *name)\n\t";

    write(STDOUT_FILENO, help, strLEN(help));
    help = "Remove an entry completely from the environment\n";
    write(STDOUT_FILENO, help, strLEN(help));
}

/**
 * helpG - Display general help information
 * Return: None
 */
void helpG(void)
{
    char *help = "^-^ bash, version 1.0(1)-release\n";

    write(STDOUT_FILENO, help, strLEN(help));
    help = "These commands are defined internally. Type 'help' to see the list";
    write(STDOUT_FILENO, help, strLEN(help));
    help = "Type 'help name' to find out more about the function 'name'.\n\n ";
    write(STDOUT_FILENO, help, strLEN(help));
    help = " alias: alias [name=['string']]\n cd: cd [-L|[-P [-e]] [-@]] ";
    write(STDOUT_FILENO, help, strLEN(help));
    help = "[dir]\nexit: exit [n]\n  env: env [option] [name=value] [command ";
    write(STDOUT_FILENO, help, strLEN(help));
    help = "[args]]\n  setenv: setenv [variable] [value]\n  unsetenv: ";
    write(STDOUT_FILENO, help, strLEN(help));
    help = "unsetenv [variable]\n";
    write(STDOUT_FILENO, help, strLEN(help));
}

/**
 * helpEX - Display help information for exit command
 * Return: None
 */
void helpEX(void)
{
    char *help = "exit: exit [n]\n Exit shell.\n";

    write(STDOUT_FILENO, help, strLEN(help));
    help = "Exits the shell with a status of N. If N is omitted, the exit";
    write(STDOUT_FILENO, help, strLEN(help));
    help = "status is that of the last command executed\n";
    write(STDOUT_FILENO, help, strLEN(help));
}
