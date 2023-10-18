#include "shell.h"

/**
 * exitSH - Handle the exit shell command
 * @datash: Pointer to data_shell struct
 * Return: 0 on success, 1 on failure
 */
int exitSH(DT_SH *datash)
{
    unsigned int ustatus;
    int is_digit;
    int str_len;
    int big_number;

    // Check if an exit status is provided
    if (datash->args[1] != NULL)
    {
        // Convert argument to unsigned int and check validity
        ustatus = iota(datash->args[1]);
        is_digit = isDgit(datash->args[1]);
        str_len = strLEN(datash->args[1]);
        big_number = ustatus > (unsigned int)INT_MAX;

        // Check if the argument is a valid unsigned int
        if (!is_digit || str_len > 10 || big_number)
        {
            getErr(datash, 2);
            datash->status = 2;
            return 1; // Return failure
        }

        // Set the exit status to the argument value (mod 256)
        datash->status = (ustatus % 256);
    }

    return 0; // Return success
}
