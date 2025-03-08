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

/**
 * @brief Reads data from a document and adds it to new stack
 * 
 * @author Arturo Pérez
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
 * @author Arturo Pérez
 *
 * @param sin1 A pointer to the first stack
 * @param sin2 A pointer to the second stack
 * @param sout A pointer to the output stack
 * 
 * @return This function returns OK if the merge was successful, otherwise ERROR.
 **/
Status mergeStacks (Stack *sin1, Stack *sin2, Stack *sout);

#endif
