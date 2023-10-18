#include "shell.h"

/**
 * fdata - Free allocated memory for data_shell struct
 * @datash: Pointer to DT_SH struct
 * Return: None
 */
void fdata(DT_SH *datash)
{
    unsigned int i;

    for (i = 0; datash->_environ[i]; i++)
    {
        free(datash->_environ[i]);
    }

    free(datash->_environ);
    free(datash->pid);
}

/**
 * sdata - Initialize data_shell struct with given arguments
 * @datash: Pointer to data_shell struct
 * @av: Argument vector (array of strings)
 * Return: None
 */
void sdata(DT_SH *datash, char **av)
{
    unsigned int i;

    // Initialize data_shell struct members
    datash->av = av;
    datash->input = NULL;
    datash->args = NULL;
    datash->status = 0;
    datash->counter = 1;

    // Count the number of environment variables
    for (i = 0; environ[i]; i++)
        ;

    // Allocate memory for _environ and copy environment variables
    datash->_environ = malloc(sizeof(char *) * (i + 1));

    for (i = 0; environ[i]; i++)
    {
        datash->_environ[i] = strDUP(environ[i]);
    }

    datash->_environ[i] = NULL;
    datash->pid = iota(getpid());
}

/**
 * main - Entry point of the shell program
 * @ac: Argument count
 * @av: Argument vector (array of strings)
 * Return: Exit status of the shell program
 */
int main(int ac, char **av)
{
    DT_SH dataSH;
    (void)ac; // Unused variable

    // Set a signal handler for SIGINT
    signal(SIGINT, getSig);

    // Initialize data_shell struct, start the shell loop, and free allocated memory
    sdata(&dataSH, av);
    sheLoop(&dataSH);
    fdata(&dataSH);

    // Return the exit status of the shell program
    if (dataSH.status < 0)
        return 255;

    return dataSH.status;
}
