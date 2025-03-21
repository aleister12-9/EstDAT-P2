/*
 * File: p2_e2.c
 * Author: Izan Robles
 */

#include "utils.h"
#include "file_utils.h"
#include "vertex.h"
#include "graph.h"

#define MAX_FILENAME 128

int main()
{
    Graph *g = NULL;
    FILE *file = NULL;
    char filename[MAX_FILENAME];
    long id_from, id_to;

    printf("\n");

    g = graph_init();
    if (!g)
    {
        printf("ERROR: could not initialize graph");
        return 1;
    }
    
    printf("\nType the graph datafile -->");
    scanf("%s", filename);

    if (!(file = fopen(filename, "r")))
    {
        printf("ERROR: could not open file\n");
        graph_free(g);
        return 1;
    }
    else
    {
        printf("DEBUG: file found and opened\n");
    }

    if (graph_readFromFile(file, g) == ERROR)
    {
        printf("ERROR: could not read graph\n");
        graph_free(g);
        fclose(file);
        return 1;
    }
    else
    {
        printf("DEBUG: graph succesfully read\n");
    }

    printf("Input graph: \n");

    if (graph_print(stdout, g) <= 0)
    {
        printf("ERROR: Could not print graph\n");
        graph_free(g);
        fclose(file);
        return 1;
    }

    do 
    {
        printf("Type id of vertex to start from -->");
        if (scanf("%ld", &id_from) != 1) 
        {
            printf("ERROR: Invalid input. Please enter a valid numeric ID.\n");
            while (getchar() != '\n'); 
            continue;
        }
        if (!graph_contains(g, id_from)) 
        {
            printf("ERROR: Vertex %ld does not exist in the graph\n", id_from);
        }

    } while (!graph_contains(g, id_from));
    
    do 
    {
        printf("Type id of vertex to end -->");
        if (scanf("%ld", &id_to) != 1) 
        {
            printf("ERROR: Invalid input. Please enter a valid numeric ID.\n");
            while (getchar() != '\n'); 
            continue;
        }
        if (!graph_contains(g, id_to)) 
        {
            printf("ERROR: Vertex %ld does not exist in the graph\n", id_to);
        }

    } while (!graph_contains(g, id_to));

    fclose(file);

    printf("Output: ");

    if (graph_depthSearch(g, id_from, id_to) == ERROR)
    {
        graph_free(g);
        printf("ERROR: Could not execute algorithm");
        return 1;
    }
    else
    {
        printf("DEBUG: algorithm succesfully executed\n");
    }
    
    graph_free(g);
    printf("\n");

    return 0;
}