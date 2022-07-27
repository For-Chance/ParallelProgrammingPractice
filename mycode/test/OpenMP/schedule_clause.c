/******************************************************************************
 * FILE: schedule_clause.c
 * DESCRIPTION:
 *   	Test schedule clause.
 * RESULT:
 *      Schedule子句能够解决负载不均衡的问题。
 * AUTHOR: Chance
 * LAST REVISED: 2022-07-27
 ******************************************************************************/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
    omp_set_num_threads(2);
    int i;
#pragma omp parallel for schedule(dynamic, 2)
    for (i = 0; i < 10; i++)
        printf("i = %d, tid = %d\n", i, omp_get_thread_num());
    system("pause");
    return 0;
}