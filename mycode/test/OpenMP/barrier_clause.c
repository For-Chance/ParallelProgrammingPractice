/******************************************************************************
 * FILE: barrier_clause.c
 * DESCRIPTION:
 *   	Test barrier.
 * RESULT:
 *   	OpenMP中的许多指令（如parallel，for，sections，critial，single等）都自身带有barrier。
 * AUTHOR: Chance
 * LAST REVISED: 2022-07-27
 ******************************************************************************/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
    int sum;
    sum = 0;
#pragma omp parallel num_threads(3)
    {
// sum = 0;
#pragma omp for
        for (int i = 0; i < 10; i++)
            sum += i;
#pragma omp barrier
        printf("tid = %d, sum = %d\n", omp_get_thread_num(), sum);
    }
    system("pause");
    return 0;
}