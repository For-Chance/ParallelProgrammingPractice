/******************************************************************************
 * FILE: critical_clause.c
 * DESCRIPTION:
 *   	Test critical.
 * RESULT:
 *      critical 提供了互斥锁机制。 将后面的区域设置为临界区，同一时间只能有一个线程执行临界区的代码
 *      aotmic 同样提供了互斥锁机制，但是aotmic只能指定单条赋值语句
 * AUTHOR: Chance
 * LAST REVISED: 2022-07-27
 ******************************************************************************/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
    int sum = 0;
    double tt = omp_get_wtime();
#pragma omp parallel for
    for (int i = 0; i < 10000000; i++)
    {
// #pragma omp critical
#pragma omp atomic
        sum += i;
    }
    printf("sum: %d, cost time = %f\n", sum, omp_get_wtime() - tt);
    system("pause");
    return 0;
}