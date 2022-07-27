/******************************************************************************
 * FILE: if_clause.c
 * DESCRIPTION:
 *   	Test if clause
 * RESULT:
 *
 * AUTHOR: Chance
 * LAST REVISED: 2022-07-27
 ******************************************************************************/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
    int ncp = omp_get_num_procs();
#pragma omp parallel if (ncp > 1)
    printf("test\n");
    system("pause");
    return 0;
}