/******************************************************************************
 * FILE: for.c
 * DESCRIPTION:
 *      Parallel programming for loop
 * AUTHOR: Chance
 * LAST REVISED: 2022-07-11
 ******************************************************************************/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int MAX = 99999;
    double res[MAX];
    int i;
    double tt = omp_get_wtime();
    for (i = 0; i < MAX; i++)
    {
        res[i] = 1;
        // printf("%d\n", i);
    }
    printf("Run time of linear programming: %.8f\n", omp_get_wtime() - tt);

    tt = omp_get_wtime();
#pragma omp prallel
    {
#pragma omp for
        for (i = 0; i < MAX; i++)
        {
            res[i] = 1;
            // printf("%d\n", i);
        }
    }
    printf("Run time of parallel programming: %.8f", omp_get_wtime() - tt);
    system("pause");
    return 0;
}