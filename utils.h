/* 
 * File: utils.h
 * Author: Arturo Pérez
 * Author: Izan Robles
 */

#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "types.h"
#include "vertex.h"
#include "graph.h"

/**
 * @brief Reads data from a document and adds it to new stack
 * 
 * @author Izan Robles
 *
 * @param file pointer to the file from which data will be read
 * 
 * @return Returns a pointer to a new stack containing the read information or NULL if an error occurs. 
 * 
 **/
Stack *stack_read_from_file(FILE *file);

/**
 * @brief Merges to ordered stacks into a new ordered stack.
 * 
 * @author Izan Robles
 *
 * @param sin1 A pointer to the first stack
 * @param sin2 A pointer to the second stack
 * @param sout A pointer to the output stack
 * 
 * @return This function returns OK if the merge was successful, otherwise ERROR.
 * 
 **/
Status mergeStacks (Stack *sin1, Stack *sin2, Stack *sout, P_stack_ele_cmp cmp_func);

/**
 * @brief Frees a stack and its elements
 * 
 * @author Izan Robles
 * 
 * @param s A pointer to the stack to be freed
 * 
 **/
void stack_free_with_elements(Stack *s);

/**
 * @brief Reads data from a document and adds it to a stack of vertex
 * 
 * @author Izan Robles
 * 
 * @param file pointer to the file from which data will be read
 * 
 * @return Returns a pointer to a new stack containing the read information or NULL if an error occurs. 
 *
 **/
Stack *stack_of_vertex_from_file(FILE *file);

/**
 * @brief: Makes a search from the origin vertex to the destination vertex of a graph using the depth-first 
 * search algorithm using an ADT Stack. It prints the path followed. 
 * 
 * @note This function does not free the graph used
 * 
 * @author Izan Robles
 *
 * @param g, Pointer to graph
 * @param from_id, id of the origin Vertex
 * @param to_id, id of the destination Vertex
 * 
 * @return The function returns OK or ERROR
 * 
**/
Status graph_depthSearch (Graph *g, long from_id, long to_id);

#endif
