#include "shell.h"

/**
 * addrVarNode - Add a new variable node to the list
 * @heAD: Pointer to a pointer to rVar (variable node)
 * @lVar: Length of the variable
 * @vAL: Value of the variable
 * @lVal: Length of the value
 * Return: Pointer to the head of the updated list
 */
rVar *addrVarNode(rVar **heAD, int lVar, char *vAL, int lVal)
{
    rVar *n, *t;

    n = malloc(sizeof(rVar));
    if (n == NULL)
        return NULL;

    n->lenVar = lVar;
    n->val = vAL;
    n->lenVal = lVal;

    n->next = NULL;
    t = *heAD;

    if (t == NULL)
    {
        *heAD = n;
    }
    else
    {
        while (t->next != NULL)
            t = t->next;
        t->next = n;
    }

    return *heAD;
}

/**
 * freerVarList - Free the memory allocated for the variable list
 * @heAD: Pointer to a pointer to rVar (variable node)
 * Return: None
 */
void freerVarList(rVar **heAD)
{
    rVar *t, *c;

    if (heAD != NULL)
    {
        c = *heAD;
        while ((t = c) != NULL)
        {
            c = c->next;
            free(t);
        }
        *heAD = NULL;
    }
}
