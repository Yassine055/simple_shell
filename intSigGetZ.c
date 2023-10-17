#include "shell.h"

/**
 * getSig -
 * @sig:
 */
void getSig(int sig)
{
    (void)sig;
    write(STDOUT_FILENO, "\n^-^ ", 5);
}
