#include "shell.h"

/**
 * checkEV - Check for environment variable in input
 * @h: Pointer to a pointer to rVar (variable node)
 * @in: Input string
 * @data: Pointer to DT_SH struct
 * Return: None
 */
void checkEV(rVar **h, char *in, DT_SH *data)
{
    int row, chr, j, lval;
    char **_envr;

    _envr = data->_environ;

    // Iterate through environment variables
    for (row = 0; _envr[row]; row++)
    {
        // Check for matching environment variable
        for (j = 1, chr = 0; _envr[row][chr]; chr++)
        {
            if (_envr[row][chr] == '=')
            {
                lval = _strlen(_envr[row] + chr + 1);
                add_rvar_node(h, j, _envr[row] + chr + 1, lval);
                return;
            }

            if (in[j] == _envr[row][chr])
                j++;
            else
                break;
        }
    }

    // Add a variable node for non-matching input
    for (j = 0; in[j]; j++)
    {
        if (in[j] == ' ' || in[j] == '\t' || in[j] == ';' || in[j] == '\n')
            break;
    }

    add_rvar_node(h, j, NULL, 0);
}

/**
 * checkVR - Check for variable references in input
 * @h: Pointer to a pointer to rVar (variable node)
 * @in: Input string
 * @st: String
 * @data: Pointer to data_shell struct
 * Return: Index of last character processed
 */
int checkVR(rVar **h, char *in, char *st, data_shell *data)
{
    int i, lst, lpd;

    lst = strLEN(st);
    lpd = strLEN(data->pid);

    for (i = 0; in[i]; i++)
    {
        // Check for variable references
        if (in[i] == '$')
        {
            // Handle different cases for variable references
            if (in[i + 1] == '?')
                addrVarNode(h, 2, st, lst), i++;
            else if (in[i + 1] == '$')
                addrVarNode(h, 2, data->pid, lpd), i++;
            else if (in[i + 1] == '\n' || in[i + 1] == '\0' || in[i + 1] == ' ' || in[i + 1] == '\t' || in[i + 1] == ';')
                addrVarNode(h, 0, NULL, 0);
            else
                checkEV(h, in + i, data);
        }
    }

    return i;
}

/**
 * replaced_input - Replace variables in input
 * @head: Pointer to a pointer to rVar (variable node)
 * @input: Input string
 * @new_input: New input string
 * @nlen: Length of the new input string
 * Return: Modified input string
 */
char *replaCT(rVar **head, char *input, char *new_input, int nlen)
{
    rVar *indx;
    int i, j, k;

    indx = *head;
    for (j = i = 0; i < nlen; i++)
    {
        if (input[j] == '$')
        {
            if (!(indx->len_var) && !(indx->len_val))
            {
                new_input[i] = input[j];
                j++;
            }
            else if (indx->len_var && !(indx->len_val))
            {
                for (k = 0; k < indx->len_var; k++)
                    j++;
                i--;
            }
            else
            {
                for (k = 0; k < indx->len_val; k++)
                {
                    new_input[i] = indx->val[k];
                    i++;
                }
                j += (indx->len_var);
                i--;
            }
            indx = indx->next;
        }
        else
        {
            new_input[i] = input[j];
            j++;
        }
    }

    return new_input;
}

/**
 * repVar - Replace variables in input
 * @input: Input string
 * @datash: Pointer to DT_SH struct
 * Return: Modified input string
 */
char *repVar(char *input, DT_SH *datash)
{
    rVar *head, *indx;
    char *status, *new_input;
    int olen, nlen;

    status = atoi(datash->status);
    head = NULL;

    olen = checkVR(&head, input, status, datash);

    if (head == NULL)
    {
        free(status);
        return input;
    }

    indx = head;
    nlen = 0;

    while (indx != NULL)
    {
        nlen += (indx->len_val - indx->len_var);
        indx = indx->next;
    }

    nlen += olen;

    new_input = malloc(sizeof(char) * (nlen + 1));
    new_input[nlen] = '\0';

    new_input = replaCT(&head, input, new_input, nlen);

    free(input);
    free(status);
    freerVarList(&head);

    return new_input;
}
