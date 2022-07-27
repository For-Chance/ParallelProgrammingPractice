/******************************************************************************
 * FILE: num_threads_clause.c
 * DESCRIPTION:
 *   	Test num_threads.
 * RESULT:
 *      Default mode is the dynamic mode.
 * AUTHOR: Chance
 * LAST REVISED: 2022-07-27
 ******************************************************************************/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
    int nthreads, nthreads_set, tid;
    omp_set_dynamic(0);
    nthreads_set = 3;
    omp_set_num_threads(nthreads_set);
    printf("set number of threads = %d\n", nthreads_set);
#pragma omp parallel private(tid, nthreads)
    {
        nthreads = omp_get_num_threads();
        tid = omp_get_thread_num();
        printf("number of threads = %d, tid = %d\n", nthreads, tid);
    }
    nthreads_set = 20;
    omp_set_num_threads(nthreads_set);
    printf("set number of threads = %d\n", nthreads_set);
#pragma omp parallel private(tid, nthreads)
    {
        nthreads = omp_get_num_threads();
        tid = omp_get_thread_num();
        printf("number of threads = %d, tid = %d\n", nthreads, tid);
    }
    system("pause");
    return 0;
}