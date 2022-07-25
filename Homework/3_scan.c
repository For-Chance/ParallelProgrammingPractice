/******************************************************************************
 * FILE: 3_scan.c
 * DESCRIPTION:
 *   	- Implement the parallel algorithm for scan operation using OpenMP
 *      - Compare the performance with the sequential algorithm
 * RESULT:
 *
 * AUTHOR: Chance
 * LAST REVISED: 2022-07-25
 ******************************************************************************/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_vector(double *T, int cols);

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
    int i;
    for (i = 0; i < n; i++)
        a[i] = (double)rand() / RAND_MAX;
    double *c = (double *)malloc(n * sizeof(double));
    double *s = (double *)malloc(n * sizeof(double));
    double *w = (double *)malloc(nthreads * sizeof(double));
    for (i = 0; i < nthreads; i++)
        w[i] = 0.0;

    // serial
    double tt = omp_get_wtime();
    c[0] = a[0];
    for (i = 1; i < n; i++)
        c[i] = c[i - 1] + a[i];
    printf("It takes %f seconds to finish computation with sequential algorithm.\n", omp_get_wtime() - tt);

    // scan operation
    omp_set_num_threads(nthreads);
    tt = omp_get_wtime();
#pragma omp parallel shared(s, a, n, nthreads) private(i)
    {
        int tid = omp_get_thread_num();
        double sl = 0.0;

        // Stage 1:
        // local scan, it will allocate n / nthreads operations
        s[0] = a[0];
#pragma omp for schedule(static) nowait
        for (i = 1; i < n; i++)
        {
            sl = s[i - 1] + a[i];
            s[i] = sl;
        }

        if (tid < nthreads - 1)
            w[tid + 1] = sl; // the w[0] = 0.0, and it don't include the last one

// synchronize the threads
#pragma omp barrier

// Stage 2:
// A singel thread performs scan operation on w
#pragma omp single
        {
            for (i = 1; i < nthreads; i++)
                w[i] = w[i - 1];
        }

        // Stage 3:
        sl = w[tid];
#pragma omp for schedule(static)
        for (i = 0; i < n; i++)
            s[i] += sl;
    }
    printf("It takes %f seconds to finish computation with scan algorithm.\n", omp_get_wtime() - tt);

    printf("Checking the result:");
    int cnt = 0;
    for (int i = 0; i < n; i++)
        if ((c[i] - s[i]) * (c[i] - s[i]) > 1.0E-10)
            cnt++;
    if (cnt == 0)
        printf("It's correct!\n");
    else
    {
        printf("It's wrong!\n");
        print_vector(c, n);
        print_vector(s, n);
    }

    return 0;
}

void print_vector(double *T, int cols)
{
    for (int i = 0; i < cols; i++)
        printf("%.2f  ", T[i]);
    printf("\n\n");
    return;
}