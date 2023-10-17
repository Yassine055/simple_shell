#include "shell.h"

/**
 * readLine - Read a line of input from the user
 * @i_eof: Pointer to an integer to store EOF indicator
 * Return: Pointer to the input string
 */
char *readLine(int *i_eof)
{
    char *input = NULL; // Pointer to input buffer
    size_t bufsize = 0;  // Initial buffer size

    // Read a line of input from stdin
    *i_eof = getline(&input, &bufsize, stdin);

    return input;
}
