/*
 * File: p2_e2.c
 * Author: Izan Robles
 */

#include "utils.h"
#include "file_utils.h"
#include "vertex.h"
#include "graph.h"

int main(int argc, char *argv[])
{
    Graph *g = NULL;
    FILE *file = NULL;
    long id_from, id_to;
    char *endptr;

    if (argc != 4)
    {
        printf("ERROR: Invalid input data\nUse: \"program <graph_file> <id_from> <id_to>\"\n");
        return 1;
    }

    g = graph_init();
    if (!g)
    {
        printf("ERROR: could not initialize graph\n");
        return 1;
    }

    if (!(file = fopen(argv[1], "r")))
    {
        printf("ERROR: could not open file\n");
        printf("Use: \"program <graph_file> <id_from> <id_to>\"\n");
        graph_free(g);
        return 1;
    }

    if (graph_readFromFile(file, g) == ERROR)
    {
        printf("ERROR: could not read graph\n");
        graph_free(g);
        fclose(file);
        return 1;
    }

    fclose(file);

    id_from = strtol(argv[2], &endptr, 10);
    if (*endptr != '\0' || id_from < 0 || !graph_contains(g, id_from))
    {
        printf("ERROR: Invalid vertex \"from\": %s\n", argv[2]);
        graph_free(g);
        return 1;
    }

    id_to = strtol(argv[3], &endptr, 10);
    if (*endptr != '\0' || id_to < 0 || !graph_contains(g, id_to))
    {
        printf("ERROR: Invalid vertex \"to\": %s\n", argv[3]);
        graph_free(g);
        return 1;
    }

    printf("Input graph: \n");
    if (graph_print(stdout, g) <= 0)
    {
        printf("ERROR: Could not print graph\n");
        graph_free(g);
        return 1;
    }

    printf("Output: ");
    if (graph_depthSearch(g, id_from, id_to) == ERROR)
    {
        printf("ERROR: Could not execute algorithm\n");
        graph_free(g);
        return 1;
    }

    graph_free(g);
    return 0;
}