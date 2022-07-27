/******************************************************************************
 * FILE: 6_2_calculate_pi.c
 * DESCRIPTION:
 *   	Using parallel programming to optimize the process of calculating pi.
 *          - critial
 *          - atomic
 *          - reduction
 * RESULT:
 *
 * AUTHOR: Chance
 * CREATE TIME: 2022-07-27
 ******************************************************************************/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 10000000

int main(int argc, char *argv[])
{
    omp_set_num_threads(10);

    double tt, sum, temp, pi1, pi2;
    int i;

    tt = omp_get_wtime();
    sum = 0.0;
    for (i = 0; i < N; i++)
    {
        temp = (i + 0.5) / N;
        sum += 4 / (1 + temp * temp);
    }
    pi1 = sum / N;
    printf("serial calculation: \t\tpi = %.30f, cost time = %f\n", pi1, omp_get_wtime() - tt);

    printf("Parallel calculation:\n");

    tt = omp_get_wtime();
    sum = 0.0;
#pragma omp parallel for shared(sum)
    for (i = 0; i < N; i++)
    {
        temp = (i + 0.5) / N;
#pragma omp critical
        sum += 4 / (1 + temp * temp);
    }
    pi2 = sum / N;
    printf("\t critial: \t\tpi = %.30f, cost time = %f \n", pi2, omp_get_wtime() - tt);

    tt = omp_get_wtime();
    sum = 0.0;
#pragma omp parallel for shared(sum)
    for (i = 0; i < N; i++)
    {
        temp = (i + 0.5) / N;
        temp = 4 / (1 + temp * temp);
#pragma omp atomic
        sum += temp;
    }
    pi2 = sum / N;
    printf("\t atomic: \t\tpi = %.30f, cost time = %f \n", pi2, omp_get_wtime() - tt);

    tt = omp_get_wtime();
    sum = 0.0;
#pragma omp parallel for reduction(+ \
                                   : sum)
    for (i = 0; i < N; i++)
    {
        temp = (i + 0.5) / N;
        temp = 4 / (1 + temp * temp);
        sum += temp;
    }
    pi2 = sum / N;
    printf("\t reduction: \t\tpi = %.30f, cost time = %f \n", pi2, omp_get_wtime() - tt);
    system("pause");
    return 0;
}