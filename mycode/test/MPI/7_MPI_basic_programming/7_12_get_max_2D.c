/******************************************************************************
 * FILE: 7_12_get_max_2D.c
 * DESCRIPTION:
 *   	Get the max number in two-dimensional matrix.
 * RESULT:
 *
 * AUTHOR: Chance
 * CREATE TIME: 2022-07-28
 ******************************************************************************/
#include <mpi.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double max_value(double **A, int row, int col);

int main(int argc, char *argv[])
{
    int size, myid, length, i, j;
    float xmax, c[5];
    double **A;
    MPI_Status status;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Get_processor_name(processor_name, &length);
    A = (double **)malloc(20 * sizeof(double *));
    for (i = 0; i < 20; i++)
        A[i] = (double *)malloc(100 * sizeof(double));
    printf("process num: %d, process id: %d, computer name: %s\n", size, myid, processor_name);
    for (i = 0; i < 20; i++)
        for (j = 0; j < 100; j++)
            A[i][j] = i * 100.0 + j + myid * 100.0 * 20;
    xmax = 0.0;
    xmax = max_value(A, 20, 100);
    printf("processor: %d, xmax: %f\n", myid, xmax);
    if (myid > 0)
        MPI_Send(&xmax, 1, MPI_DOUBLE, 0, myid, MPI_COMM_WORLD);
    else
    {
        c[0] = xmax;
        for (i = 1; i < 5; i++)
            MPI_Recv(c + i, 1, MPI_DOUBLE, i, i, MPI_COMM_WORLD, &status);
        xmax = 0.0;
        for (i = 0; i < size; i++)
            if (fabs(c[i]) > xmax)
                xmax = fabs(c[i]);
        printf("finial xmax = %f\n", xmax);
    }
    MPI_Finalize();
    return 0;
}

double max_value(double **A, int row, int col)
{
    double max_v = -99999999.0;
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            if (A[i][j] > max_v)
                max_v = A[i][j];
    return max_v;
}