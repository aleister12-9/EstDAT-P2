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

Status mergeStacks (Stack *sin1, Stack *sin2, Stack *sout, P_stack_ele_cmp cmp_func)
{
    void *temp = NULL;
    float *val1, *val2;
    
    if (!sin1 || !sin2 || !sout || !cmp_func)
    {
        return ERROR;
    }

    while (!stack_isEmpty(sin1) && !stack_isEmpty(sin2))
    {
        val1 = (float *)stack_top(sin1);
        val2 = (float *)stack_top(sin2);

        if (cmp_func((const void*)val1, (const void*)val2) >= 0)
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

/* ------------------------------------------------------------- */

Stack *stack_of_vertex_from_file(FILE *file)
{
    Stack *p_new_stack;
    Vertex *temp_vertex;
    char temp[MAX_DATA];
    int n_elements;
    int i;

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
        if (fgets(temp, MAX_DATA, file) == NULL)
        {
            stack_free_with_elements(p_new_stack);
            return NULL;
        }

        temp[strcspn(temp, "\n")] = 0;
        
        temp_vertex = vertex_initFromString(temp);
        if (!temp_vertex)
        {
            stack_free_with_elements(p_new_stack);
            return NULL;
        }

        if (stack_push(p_new_stack, temp_vertex) == ERROR)
        {
            vertex_free(temp_vertex);
            stack_free_with_elements(p_new_stack);
            return NULL;
        }
    }

    return p_new_stack;
}

/* ------------------------------------------------------------- */

Status graph_depthSearch (Graph *g, long from_id, long to_id)
{
    int i, num_vertices;
    Stack *st = NULL;
    Vertex **vertex_array = NULL;

    if (is_invalid_graph(g) || from_id < 0 || to_id < 0)
    {
        return ERROR;
    }
    
    /*Print input graph*/
    printf("Input Graph:\n");
    if (graph_print(stdout, g) <= 0)
    {
        printf("Could not print graph");
    }

    /*Set all vertices to white*/
    if (graph_set_all_vertex_label(g, WHITE) == ERROR)
    {
        printf("Could not perform algorithm (Code 001)");
    }

    /*Execute algorithm*/
    if (!(st = stack_init()))
    {
        return ERROR;
    }

    if ((num_vertices = graph_getNumberOfVertices(g)) < 0)
    {
        printf("Could not perform algorithm (Code 002)");        
        stack_free_with_elements(st);
        return ERROR;
    }
    
    if (!(vertex_array = graph_get_vertex_array(g)))
    {
        printf("Could not perform algorithm (Code 003)");        
        stack_free_with_elements(st);
        return ERROR;
    }

    for (i = 0; i < num_vertices; i++)
    {
        if (vertex_getId(vertex_array[i]) == from_id)
        {
            break;
        }
    }
    
    








    stack_free_with_elements(st);
    
    return OK;
}