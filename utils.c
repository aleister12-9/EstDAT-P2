/* 
 * File: utils.c
 * Author: Arturo Pérez
 * Author: Izan Robles
 */

#include "utils.h"

/* ------------------------------------------------------------- */

Stack *stack_read_from_file(FILE *file)
{
    int i;
    int n_elements = 0; 
    Stack *p_new_stack;
    float temp;
    float *p_value;
    
    /*Argument control*/
    if (!file)
    {
        return NULL;
    }

    /*Create new stack*/
    p_new_stack = stack_init();
    if (!p_new_stack)
    {
        return NULL;
    }

    /*Read number of elements*/
    rewind(file);
    if (fscanf(file, "%d\n", &n_elements) != 1)
    {
        stack_free(p_new_stack);
        return NULL;
    }
    if (n_elements <= 0)
    {
        stack_free(p_new_stack);
        return NULL;
    }
    
    /*Add new elements to the stack*/
    for (i = 0; i < n_elements; i++)
    {
        if (fscanf(file, "%f\n", &temp) != 1)
        {
            stack_free(p_new_stack);
            return NULL;
        }

        p_value = malloc(sizeof(float));
        if (!p_value)
        {
            stack_free(p_new_stack);
            return NULL;
        }
        *p_value = temp;

        if (stack_push(p_new_stack, p_value) == ERROR)
        {
            free(p_value);
            stack_free(p_new_stack);
            return NULL;
        }
    }

    /*Comprobar si hay que liberar p_value*/

    return p_new_stack;
}

/* ------------------------------------------------------------- */

Status mergeStacks (Stack *sin1, Stack *sin2, Stack *sout)
{
    void *temp = NULL;
    
    if (!sin1 || !sin2 || !sout)
    {
        return ERROR;
    }

    while (!stack_isEmpty(sin1) && !stack_isEmpty(sin2))
    {
        if (stack_top(sin1) > stack_top(sin2) || stack_top(sin1) == stack_top(sin2))
        {
            temp = stack_pop(sin1);
            if (stack_push(sout, temp) == ERROR)
            {
                return ERROR;
            }
        }

        else if (stack_top(sin1) < stack_top(sin2))
        {
            temp = stack_pop(sin2);
            if (stack_push(sout, temp) == ERROR)
            {
                return ERROR;
            }
        }
    }

    while (!stack_isEmpty(sin2))
    {
        temp = stack_pop(sin2);
        if (stack_push(sout, temp) == ERROR)
        {
            return ERROR;
        }
    }
    
    while (!stack_isEmpty(sin1))
    {
        temp = stack_pop(sin1);
        if (stack_push(sout, temp) == ERROR)
        {
            return ERROR;
        }
    }
    
    return OK;
}
