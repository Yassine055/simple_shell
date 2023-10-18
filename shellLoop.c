#include "shell.h"

/**
 * withoutComm - Remove comments from input string
 * @in: Input string
 * Return: Modified input string without comments
 */
char *withoutComm(char *in)
{
    int i, up_to;

    up_to = 0;

    // Search for '#' to identify comments
    for (i = 0; in[i]; i++)
    {
        if (in[i] == '#')
        {
            if (i == 0)
            {
                free(in);
                return NULL;
            }

            if (in[i - 1] == ' ' || in[i - 1] == '\t' || in[i - 1] == ';')
                up_to = i;
        }
    }

    if (up_to != 0)
    {
        in = rC(in, i, up_to + 1);
        in[up_to] = '\0';
    }

    return in;
}

/**
 * sheLoop - Shell main loop
 * @datash: Pointer to data_shell struct
 * Return: None
 */
void sheLoop(DT_SH *datash)
{
    int loop, i_eof;
    char *input;

    loop = 1;

    while (loop == 1)
    {
        write(STDIN_FILENO, "^-^ ", 4);
        input = readLine(&i_eof);

        if (i_eof != -1)
        {
            input = withoutComm(input);
            if (input == NULL)
                continue;

            if (pSyErr(datash, input) == 1)
            {
                datash->status = 2;
                free(input);
                continue;
            }

            input = reVar(input, datash);
            loop = sComm(datash, input);
            datash->counter += 1;
            free(input);
        }
        else
        {
            loop = 0;
            free(input);
        }
    }
}
