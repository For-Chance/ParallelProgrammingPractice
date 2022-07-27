/******************************************************************************
 * FILE: 6_1_loop.c
 * DESCRIPTION:
 *   	Test the performance of parallel loop.
 * RESULT:
 *      线程不是越多越好
 * AUTHOR: Chance
 * CREATE TIME: 2022-07-27
 ******************************************************************************/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
const int N = 40000;

void test()
{
    for (int i = 0; i < N; i++)
    {
    }
}

int main(int argc, char *argv[])
{
    double tt;
    tt = omp_get_wtime();
#pragma omp parallel for num_threads(1)
    for (int i = 0; i < N; i++)
        test();
    printf("num_threads = 1, cost time = %f\n", omp_get_wtime() - tt);
    tt = omp_get_wtime();
#pragma omp parallel for num_threads(2)
    for (int i = 0; i < N; i++)
        test();
    printf("num_threads = 2, cost time = %f\n", omp_get_wtime() - tt);
    tt = omp_get_wtime();
#pragma omp parallel for num_threads(4)
    for (int i = 0; i < N; i++)
        test();
    printf("num_threads = 4, cost time = %f\n", omp_get_wtime() - tt);
    tt = omp_get_wtime();
#pragma omp parallel for num_threads(8)
    for (int i = 0; i < N; i++)
        test();
    printf("num_threads = 8, cost time = %f\n", omp_get_wtime() - tt);
    tt = omp_get_wtime();
#pragma omp parallel for num_threads(12)
    for (int i = 0; i < N; i++)
        test();
    printf("num_threads = 12, cost time = %f\n", omp_get_wtime() - tt);
    system("pause");
    return 0;
}