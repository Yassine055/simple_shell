#include "shell.h"

/**
 * mC -
 * @newpt:
 * @ptr:
 * @z:
 *
 * Return:
 */
void mC(void *newpt, const void *ptr, unsigned int z)
{
    char *charPtr = (char *)ptr;
    char *charNewpt = (char *)newpt;
    unsigned int i;

    for (i = 0; i < z; i++)
        charNewpt[i] = charPtr[i];
}

/**
 * rC -
 * @ptr:
 * @oldsize:
 * @newsize:
 *
 * Return:
 */
void *rC(void *ptr, unsigned int oldSize, unsigned int newSize)
{
    void *newptr;

    if (ptr == NULL)
        return (malloc(newSize));

    if (newSize == 0)
    {
        free(ptr);
        return (NULL);
    }

    newptr = malloc(newSize);
    if (newptr == NULL)
        return (NULL);

    if (newSize < oldSize)
        mC(newptr, ptr, newSize);
    else
        mC(newptr, ptr, oldSize);

    free(ptr);
    return (newptr);
}

/**
 * rCDP -
 * @ptr:
 * @oldsize:
 * @newsize:
 *
 * Return:
 */
char **rCDP(char **ptr, unsigned int oldSize, unsigned int newSize)
{
    char **newptr;
    unsigned int i;

    if (ptr == NULL)
        return (malloc(sizeof(char *) * newSize));

    if (newSize == oldSize)
        return (ptr);

    newptr = malloc(sizeof(char *) * newSize);
    if (newptr == NULL)
        return (NULL);

    for (i = 0; i < oldSize; i++)
        newptr[i] = ptr[i];

    free(ptr);

    return (newptr);
}
