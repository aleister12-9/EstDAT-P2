/*
 * File: p2_e1a.c
 * Author: Izan Robles
 */

#include "utils.h"
#include "file_utils.h"

int main(int argc, char *argv[])
{
    FILE *file = NULL;
    int error_manager = 0;
    Stack *sin1 = NULL;
    Stack *sin2 = NULL;
    Stack *sout = NULL;
    P_stack_ele_print print_func = _float_print;

    if (argc != 3)
    {
        printf("Use: program <data_file_1.txt> <data_file_2.tx>\n");
        return 1;
    }
    

    /*Read first file and create stack*/
    if (!(file = fopen(argv[1], "r")))
    {
        printf("Could not open first file\n");
        return 1;
    }

    sin1 = stack_read_from_file(file);
    if (!sin1)
    {
        printf("Could not read information\n");
        fclose(file);
        return 1;
    }

    fclose(file);

    /*Print first ranking*/
    printf("Ranking 0:\n");
    if ((error_manager = stack_print(stdout, sin1, print_func)) < 0)
    {
        printf("Could not print first ranking\n");
        stack_free_with_elements(sin1);
        return 1;
    }

    /*Read second file and create stack*/
    if (!(file = fopen(argv[2], "r")))
    {
        printf("Could not open second file\n");
        stack_free_with_elements(sin1);
        return 1;
    }

    sin2 = stack_read_from_file(file);
    if (!sin2)
    {
        printf("Could not read information\n");
        fclose(file);
        stack_free_with_elements(sin1);
        return 1;
    }

    fclose(file);

    /*Print second ranking*/
    printf("\nRanking 1:\n");
    if ((error_manager = stack_print(stdout, sin2, print_func)) < 0)
    {
        printf("Could not print second ranking\n");
        stack_free_with_elements(sin1);
        stack_free_with_elements(sin2);
        return 1;
    }

    /*Create new stack and merge*/
    sout = stack_init();
    if (!sout)
    {
        printf("Could not create output stack\n");
        stack_free_with_elements(sin1);
        stack_free_with_elements(sin2);
        return 1;
    }

    if (mergeStacks(sin1, sin2, sout, float_cmp) == ERROR)
    {
        printf("Could not merge stacks\n");
        stack_free_with_elements(sin1);
        stack_free_with_elements(sin2);
        stack_free_with_elements(sout);
        return 1;
    }

    /*Print joint ranking*/
    printf("\nJoint Ranking:\n");
    if ((error_manager = stack_print(stdout, sout, print_func)) < 0)
    {
        printf("Could not print joint ranking\n");
        stack_free_with_elements(sin1);
        stack_free_with_elements(sin2);
        stack_free_with_elements(sout);
        return 1;
    }

    stack_free_with_elements(sin1);
    stack_free_with_elements(sin2);
    stack_free_with_elements(sout);
    printf("\n");
    return 0;
}
