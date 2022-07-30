/******************************************************************************
 * FILE: 7_17_circle_message.c
 * DESCRIPTION:
 *   	Demo for circle message.
 * RESULT:
 *
 * AUTHOR: Chance
 * CREATE TIME: 2022-07-29
 ******************************************************************************/
#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int rank, size, m, n, next, front;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    m = n = rank * 100;
    front = (size + rank - 1) % size;
    next = (rank + 1) % size;
    printf("Before communication. rank = %d, front = %d, next = %d;m = %d;n = %d\n", rank, front, next, m, n);
    if (rank == 0)
    {
        MPI_Recv(&n, 1, MPI_INT, front, 1, MPI_COMM_WORLD, &status);
        MPI_Send(&m, 1, MPI_INT, next, 1, MPI_COMM_WORLD);
    }
    else
    {
        MPI_Send(&m, 1, MPI_INT, next, 1, MPI_COMM_WORLD);
        MPI_Recv(&n, 1, MPI_INT, front, 1, MPI_COMM_WORLD, &status);
    }
    printf("After communication. rank = %d, m = %d, n = %d\n", rank, m, n);
    MPI_Finalize();
    return 0;
}