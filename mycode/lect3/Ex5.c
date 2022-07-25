/******************************************************************************
 * FILE: Ex5.c
 * DESCRIPTION:
 *   	Compare the performance of these two routines as follows:
 *          - One uses OpenMP reduction clause
 *          - The other is to let each thread compute a paritial sum and then accumulate the partial sums
 * RESULT:
 *      run: ./Ex5.exe 100000000 10
 *          1. Only the answer of second program is wrong, so we can not directly do a multiple threads for a program with loop carried data dependency.
 *          2. The running speed of two methods in DESCRIPTION are almost same while the reduction operation is more simple.
 * AUTHOR: Chance
 * LAST REVISED: 2022-07-25
 ******************************************************************************/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
    int n, nthreads;
    if (argc == 3)
    {
        n = atoi(argv[1]);
        nthreads = atoi(argv[2]);
        printf("n = %d, nthreads = %d\n\n", n, nthreads);
    }
    else
    {
        printf("Usage: %s n nthreads\n"
               "n: \t\tn numbers for summation\n"
               "nthreads: \tthe number of threads\n\n",
               argv[0]);
        return 1;
    }

    // initialize
    double *a = (double *)malloc(n * sizeof(double));
    for (int i = 0; i < n; i++)
        a[i] = (double)rand() / RAND_MAX;
    double sum;
    int i;

    // serial
    omp_set_num_threads(1);
    double tt = omp_get_wtime();
#pragma omp parallel shared(a, n) private(i)
    {
        sum = 0.0;
#pragma omp for nowait
        for (i = 0; i < n; i++)
            sum += a[i];
    }
    printf("Result: %f, it takes %f seconds to finish computation with one thread.\n", sum, omp_get_wtime() - tt);

    // multiple threads
    omp_set_num_threads(nthreads);
    tt = omp_get_wtime();
#pragma omp parallel shared(a, n) private(i)
    {
        sum = 0.0;
#pragma omp for nowait
        for (i = 0; i < n; i++)
            sum += a[i];
    }
    printf("Result: %f, it takes %f seconds to finish computation with %d threads.\n", sum, omp_get_wtime() - tt, nthreads);

    // partical sum
    omp_set_num_threads(nthreads);
    tt = omp_get_wtime();
    sum = 0.0;
#pragma omp parallel shared(a, sum, n) private(i)
    {
        double sumi = 0.0;
#pragma omp for nowait
        for (i = 0; i < n; i++)
            sumi += a[i];
#pragma omp atomic
        sum += sumi;
    }
    printf("Result: %f, it takes %f seconds to finish computation with %d threads and partical sum.\n", sum, omp_get_wtime() - tt, nthreads);

    // reduction clause
    omp_set_num_threads(nthreads);
    tt = omp_get_wtime();
#pragma omp parallel shared(a, n) private(i)
    {
        sum = 0.0;
#pragma omp for nowait, reduction(+ \
                                  : sum)
        for (i = 0; i < n; i++)
            sum += a[i];
    }
    printf("Result: %f, it takes %f seconds to finish computation with %d threads and reduction clause.\n", sum, omp_get_wtime() - tt, nthreads);
    return 0;
}