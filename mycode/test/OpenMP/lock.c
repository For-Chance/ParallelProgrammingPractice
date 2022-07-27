/******************************************************************************
 * FILE: lock.c
 * DESCRIPTION:
 *   	Test lock.
 * RESULT:
 *
 * AUTHOR: Chance
 * CREATE TIME: 2022-07-27
 ******************************************************************************/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static omp_lock_t lock;
int main(int argc, char *argv[])
{
    omp_init_lock(&lock);
#pragma omp parallel for num_threads(3)
    for (int i = 0; i < 5; i++)
    {
        omp_set_lock(&lock);
        printf("i = %d, tid = %d, +\n", i, omp_get_thread_num());
        printf("i = %d, tid = %d, -\n", i, omp_get_thread_num());
        omp_unset_lock(&lock);
    }
    omp_destroy_lock(&lock);
    system("pause");
    return 0;
}