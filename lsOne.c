#include "shell.h"

/**
 * addSNEnd -  
 * @head:
 * @sep:  ; | &
 * Return:
 */
sList *addSNEnd(sList **head, char sep)
{
    sList *n, *t;

    n = malloc(sizeof(sList));
    if (n == NULL)
        return (NULL);

    n->separator = sep;
    n->next = NULL;
    t = *head;

    if (t == NULL)
    {
        *head = n;
    }
    else
    {
        while (t->next != NULL)
            t = t->next;
        t->next = n;
    }

    return (*head);
}

/**
 * freeSList -
 * @head:
 * Return:
 */
void freeSList(sList **head)
{
    sList *t;
    sList *c;

    if (head != NULL)
    {
        c = *head;
        while ((t = c) != NULL)
        {
            c = c->next;
            free(t);
        }
        *head = NULL;
    }
}

/**
 * addLNEnd -
 * @head:
 * @line:
 * Return:
 */
line_list *addLNEnd(lList **head, char *l)
{
    lList *n, *t;

    n = malloc(sizeof(lList));
    if (n == NULL)
        return (NULL);

    n->line = l;
    n->next = NULL;
    t = *head;

    if (t == NULL)
    {
        *head = n;
    }
    else
    {
        while (t->next != NULL)
            t = t->next;
        t->next = n;
    }

    return (*head);
}

/**
 * freeLList -
 * @head:
 * Return:
 */
void freeLList(lList **head)
{
    lList *t;
    lList *c;

    if (head != NULL)
    {
        c = *head;
        while ((t = c) != NULL)
        {
            c = c->next;
            free(t);
        }
        *head = NULL;
    }
}
