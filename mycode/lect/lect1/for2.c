/******************************************************************************
 * FILE: for2.c
 * DESCRIPTION:
 *   	demo
 * AUTHOR: Chance
 * LAST REVISED: 2022-07-11
 ******************************************************************************/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int MAX = 510000;
    int i, j, A[MAX];

    double start = omp_get_wtime();
    j = 5;
    for (int i = 0; i < MAX; i++)
    {
        j += 2;
        A[i] = j;
    }
    double end = omp_get_wtime();
    printf("Running time with dependencies: %f\n", end - start);

    start = omp_get_wtime();
#pragma omp parallel for
    for (int i = 0; i < MAX; i++)
    {
        int j = 5 + 2 * (i + 1);
        A[i] = j;
    }
    end = omp_get_wtime();
    printf("Running time without dependencies: %f\n", end - start);
    system("pause");
    return 0;
}