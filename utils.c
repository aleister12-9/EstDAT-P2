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
        stack_free_with_elements(p_new_stack);
        return NULL;
    }
    if (n_elements <= 0)
    {
        stack_free_with_elements(p_new_stack);
        return NULL;
    }
    
    /*Add new elements to the stack*/
    for (i = 0; i < n_elements; i++)
    {
        if (fscanf(file, "%f\n", &temp) != 1)
        {
            stack_free_with_elements(p_new_stack);
            return NULL;
        }

        p_value = malloc(sizeof(float));
        if (!p_value)
        {
            stack_free_with_elements(p_new_stack);
            return NULL;
        }
        *p_value = temp;

        if (stack_push(p_new_stack, p_value) == ERROR)
        {
            free(p_value);
            stack_free_with_elements(p_new_stack);
            return NULL;
        }
    }

    return p_new_stack;
}

/* ------------------------------------------------------------- */

Status mergeStacks (Stack *sin1, Stack *sin2, Stack *sout)
{
    void *temp = NULL;
    float *val1, *val2;
    
    if (!sin1 || !sin2 || !sout)
    {
        return ERROR;
    }

    while (!stack_isEmpty(sin1) && !stack_isEmpty(sin2))
    {
        val1 = (float *)stack_top(sin1);
        val2 = (float *)stack_top(sin2);

        if (*val1 >= *val2)
        {
            temp = stack_pop(sin1);
            if (stack_push(sout, temp) == ERROR)
            {
                return ERROR;
            }
        }
        else
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

/* ------------------------------------------------------------- */

void stack_free_with_elements(Stack *s)
{
    void *elem;
    while (!stack_isEmpty(s))
    {
        elem = stack_pop(s);
        if (elem)
        {
            free(elem);
        }
    }
    stack_free(s);
}