/******************************************************************************
 * FILE: master_clause.c
 * DESCRIPTION:
 *   	Test master
 * RESULT:
 *      - master 要求主线程执行
 *      - single 要求任意一个线程执行
 * AUTHOR: Chance
 * CREATE TIME: 2022-07-27
 ******************************************************************************/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
#pragma omp parallel num_threads(3)
    {
        for (int i = 0; i < 5; i++)
            printf("i = %d, tid = %d\n", i, omp_get_thread_num());
#pragma omp single
        printf("----------------------------------\n");
#pragma omp master
        for (int i = 0; i < 5; i++)
            printf("i = %d, tid = %d\n", i, omp_get_thread_num());
    }
    system("pause");
    return 0;
}