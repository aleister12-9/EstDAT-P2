/*
 * File: p2_e2.c
 * Author: Izan Robles
 */

#include "utils.h"
#include "file_utils.h"
#include "vertex.h"
#include "graph.h"

int main()
{

    /* --------------------------------- TEMPORAL FOR TESTING --------------------------------- */

    Graph *g = NULL;
    FILE *file = NULL;

    g = graph_init();
    if (!g)
    {
        printf("Could not initialize graph");
        return 1;
    }
    
    
    if (!(file = fopen("g2.txt", "r")))
    {
        printf("Couldnt open file\n");
        graph_free(g);
        return 1;
    }

    if (graph_readFromFile(file, g) == ERROR)
    {
        printf("Could not read graph\n");
        graph_free(g);
        fclose(file);
        return 1;
    }

    fclose(file);

    if (graph_print(stdout, g) <= 0)
    {
        printf("Could not print graph\n");
        graph_free(g);
        return 1;
    }

    graph_free(g);

    /* --------------------------------- TEMPORAL FOR TESTING --------------------------------- */

    return 0;
}