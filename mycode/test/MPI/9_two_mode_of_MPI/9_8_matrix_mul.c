/******************************************************************************
 * FILE: 9_8_matrix_mul.c
 * DESCRIPTION:
 *      matrix multiplication using MPI.
 * RESULT:
 *
 * AUTHOR: Chance
 * CREATE TIME: 2022-07-30
 ******************************************************************************/
#include <mpi.h>
#include <stdio.h>
#define ROWS 100
#define COLS 100
#define min(x, y) ((x) > (y) ? (y) : (x))
int main(int argc, char *argv[])
{
    int rows = ROWS, cols = COLS, master = 0, myid, numprocs, i, j;
    double a[ROWS][COLS], b[COLS], c[COLS], row_result;
    MPI_Status status;
    MPI_Comm comm = MPI_COMM_WORLD;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(comm, &myid);
    MPI_Comm_size(comm, &numprocs);
    if (master == myid)
    {
        for (j = 0; j < cols; j++)
            b[j] = 1;
        for (i = 0; i < rows; i++)
            for (j = 0; j < cols; j++)
                a[i][j] = i;
        // MPI_Barrier(comm);
        double tt = MPI_Wtime();
        MPI_Bcast(&b[0], cols, MPI_DOUBLE, master, comm);
        int numsent = 0;
        for (i = 1; i < min(numprocs, rows + 1); i++)
            MPI_Send(&a[i - 1][0], cols, MPI_DOUBLE, i, ++numsent, comm);
        for (i = 0; i < rows; i++)
        {
            MPI_Recv(&row_result, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, comm, &status);
            c[status.MPI_TAG - 1] = row_result;
            if (numsent < rows)
            {
                MPI_Send(&a[numsent][0], cols, MPI_DOUBLE, status.MPI_SOURCE, numsent + 1, comm);
                numsent++;
            }
            else
                MPI_Send(&a[numsent][0], 0, MPI_DOUBLE, status.MPI_SOURCE, 0, comm);
        }
        // MPI_Barrier(comm);
        printf("cost time is %fs\n", MPI_Wtime() - tt);
        // for (j = 0; j < cols; j++)
        //     printf("%1.3f\t", c[j]);
        // printf("\n");
    }
    else
    {
        MPI_Bcast(&b[0], cols, MPI_DOUBLE, master, comm);
        while (1)
        {
            row_result = 0;
            MPI_Recv(&c[0], cols, MPI_DOUBLE, master, MPI_ANY_TAG, comm, &status);
            if (0 != status.MPI_TAG)
            {
                for (j = 0; j < cols; j++)
                    row_result = row_result + b[j] * c[j];
                MPI_Send(&row_result, 1, MPI_DOUBLE, master, status.MPI_TAG, comm);
            }
            else
                break;
        }
    }
    MPI_Finalize();
    return 0;
}