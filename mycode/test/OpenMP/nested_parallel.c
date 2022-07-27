/******************************************************************************
 * FILE: nested_parallel.c
 * DESCRIPTION:
 *   	Test nested parallel.
 * RESULT:
 *      如果设置不能嵌套，但是代码包含了嵌套程序，那么最后会以串行的形式执行
 * AUTHOR: Chance
 * LAST REVISED: 2022-07-27
 ******************************************************************************/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
    int i, j, k;
    k = omp_get_nested();
    printf("Nested Parallel: %d\n", k);
    omp_set_nested(1);
    k = omp_get_nested();
    printf("Nested Parallel: %d\n", k);
#pragma omp parallel for num_threads(3)
    for (i = 0; i < 3; i++)
    {
#pragma omp parallel for num_threads(4)
        for (j = 0; j < 4; j++)
        {
            printf("i = %d, j = %d, tid = %d, number of threads = %d\n", i, j, omp_get_thread_num(), omp_get_num_threads());
        }
        printf("---------------------------------------\n");
        printf("ttid = %d, number of threads = %d\n", omp_get_thread_num(), omp_get_num_threads());
    }
    system("pause");
    return 0;
}