/******************************************************************************
 * FILE: single_clause.c
 * DESCRIPTION:
 *   	Test single.
 * RESULT:
 *      single 子句确定后一句在并行区域内只用某一线程运行一次
 * AUTHOR: Chance
 * LAST REVISED: 2022-07-27
 ******************************************************************************/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
    int i;
#pragma omp parallel num_threads(12)
    {
#pragma omp for
        for (i = 0; i < 10; i++)
        {
            printf("i = %d, tid = %d\n", i, omp_get_thread_num());
        }
#pragma omp single nowait
        printf("\ttid = %d, num_threads = %d, printf once\n", omp_get_thread_num(), omp_get_num_threads());
    }
    system("pause");
    return 0;
}