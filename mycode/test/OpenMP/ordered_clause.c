/******************************************************************************
 * FILE: ordered_clause.c
 * DESCRIPTION:
 *   	Test ordered
 * RESULT:
 *      - 让for按顺序执行
 *   	- for 循环中只能出现一次 ordered
 * AUTHOR: Chance
 * CREATE TIME: 2022-07-27
 ******************************************************************************/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
#pragma omp parallel for ordered num_threads(3)
    for (int i = 0; i < 5; i++)
    {
#pragma omp ordered
        printf("i = %d, tid = %d\n", i, omp_get_thread_num());
    }
    system("pause");
    return 0;
}