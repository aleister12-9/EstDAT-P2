/**
 * @file  utils.c
 * @author Izan Robles
 * @brief Toolset for using different datatypes
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

Status mergeStacks(Stack *sin1, Stack *sin2, Stack *sout, P_stack_ele_cmp cmp_func)
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

        if (cmp_func((const void *)val1, (const void *)val2) >= 0)
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

Status graph_depthSearch(Graph *g, long from_id, long to_id)
{
    int i, j, num_vertices;
    Stack *st = NULL;
    Vertex **vertex_array = NULL;
    Vertex *current = NULL;
    Vertex *neighbor = NULL;
    long *connections = NULL;
    int n_connections = 0;

    if (is_invalid_graph(g) || from_id < 0 || to_id < 0)
    {
        return ERROR;
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
        stack_free(st);
        printf("Could not perform algorithm (Code 002)");
        return ERROR;
    }

    if (!(vertex_array = graph_get_vertex_array(g)))
    {
        stack_free(st);
        printf("Could not perform algorithm (Code 003)");
        return ERROR;
    }

    /*Find "from" vertex, paint black and add to stack*/
    for (i = 0; i < num_vertices; i++) {
        if (vertex_getId(vertex_array[i]) == from_id) {
            vertex_setState(vertex_array[i], BLACK);
            stack_push(st, vertex_array[i]);
            break;
        }
    }

    /*Main loop for algorithm*/
    printf("From vertex ID: %ld\n", from_id);
    printf("To vertex id: %ld\n", to_id);

    while (!stack_isEmpty(st))
    {
        current = stack_pop(st);
        vertex_print(stdout, current);
        printf("\n");

        /* Check if we found target */
        if (vertex_getId(current) == to_id)
        {
            stack_free(st);
            return OK;
        }

        /* Get connections for current vertex */
        n_connections = graph_getNumberOfConnectionsFromId(g, vertex_getId(current));
        if (n_connections < 0)
        {
            stack_free(st);
            return ERROR;
        }

        connections = graph_getConnectionsFromId(g, vertex_getId(current));
        if (!connections && n_connections > 0)
        {
            stack_free(st);
            return ERROR;
        }

        /* Add unvisited neighbors to stack */
        for (j = 0; j < n_connections; j++)
        {
            /* Find neighbor vertex object from its ID */
            for (i = 0; i < num_vertices; i++)
            {
                if (vertex_getId(vertex_array[i]) == connections[j])
                {
                    neighbor = vertex_array[i];
                    break;
                }
            }

            /* If neighbor is unvisited, mark it and add to stack */
            if (vertex_getState(neighbor) == WHITE)
            {
                vertex_setState(neighbor, BLACK);
                if (stack_push(st, neighbor) == ERROR)
                {
                    stack_free(st);
                    free(connections);
                    return ERROR;
                }
            }
        }

        if (connections)
        {
            free(connections);
        }
    }

    stack_free(st);

    return OK;
}