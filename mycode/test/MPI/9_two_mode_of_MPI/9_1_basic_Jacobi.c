/******************************************************************************
 * FILE: 9_1_basic_Jacobi.c
 * DESCRIPTION:
 *   	Serial programming for Jacobi iteration.
 * RESULT:
 *      N = 500, step = 100, cost time = 0.36~0.41s
 * AUTHOR: Chance
 * CREATE TIME: 2022-07-29
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"
#define N 500
void print_myRows(double *myRows);
int main(int argc, char *argv[])
{
    double *myRows = (double *)malloc(sizeof(double) * N * N);
    double *myRows2 = (double *)malloc(sizeof(double) * N * N);
    int myid, size, errorcode;
    double diffval = 0;
    double tempdata = 0;
    double start_time = 0;
    double end_time = 0;
    MPI_Comm comm = MPI_COMM_WORLD;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(comm, &myid);
    MPI_Comm_size(comm, &size);
    int i, j;
    /*初始化*/
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            if (i == 0 || i == N - 1 || j == 0 || j == N - 1)
            {
                myRows[i * N + j] = 8.0;
                myRows2[i * N + j] = 8.0;
            }
            else
            {
                myRows[i * N + j] = 0;
                myRows2[i * N + j] = 0;
            }
        }
    }
    // printf("Initialize:\n");
    // print_myRows(myRows);
    /*Jacobi Iteration部分*/
    MPI_Barrier(MPI_COMM_WORLD);
    start_time = MPI_Wtime();
    int step = 100;
    for (int st = 0; st < step; st++)
    {
        for (i = 1; i < N - 1; i++)
        {
            for (j = 1; j < N - 1; j++)
                myRows2[i * N + j] = 0.25 * (myRows[i * N + j - 1] + myRows[i * N + j + 1] + myRows[(i - 1) * N + j] + myRows[(i + 1) * N + j]);
        }
        // 更新
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < N; j++)
            {
                // diffval = fabs(myRows2[i * N + j] - myRows[i * N + j]);
                // diff = fmax(diffval, diff);
                myRows[i * N + j] = myRows2[i * N + j];
            }
        }
        // printf("the value is %lf\n",diff);
    }
    // 结果矩阵输出
    MPI_Barrier(MPI_COMM_WORLD);
    end_time = MPI_Wtime();
    // printf("Result:\n");
    // print_myRows(myRows);
    MPI_Finalize();
    printf("Serial total time is %lf\n", end_time - start_time);
    free(myRows);
    free(myRows2);
}

void print_myRows(double *myRows)
{
    int i, j;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            printf("%.3f ", myRows[i * N + j]);
        }
        printf("\n");
    }
}
