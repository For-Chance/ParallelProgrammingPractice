/******************************************************************************
 * FILE: sections_clause.c
 * DESCRIPTION:
 *   	Test sections.
 * RESULT:
 *      为非循环语句并行
 * AUTHOR: Chance
 * LAST REVISED: 2022-07-27
 ******************************************************************************/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
#pragma omp parallel sections num_threads(4)
    {
#pragma omp section
        printf("1, tid = %d\n", omp_get_thread_num());
#pragma omp section
        printf("2, tid = %d\n", omp_get_thread_num());
#pragma omp section
        printf("3, tid = %d\n", omp_get_thread_num());
#pragma omp section
        printf("4, tid = %d\n", omp_get_thread_num());
    }
    system("pause");
    return 0;
}