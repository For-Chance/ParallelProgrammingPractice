/******************************************************************************
 * FILE: 7_18_communiction.c
 * DESCRIPTION:
 *   	communicate between each processor.
 * AUTHOR: Chance
 * LAST REVISED: 2022-07-29
 ******************************************************************************/
#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int rank, size, errorcode;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (size < 2)
        MPI_Abort(MPI_COMM_WORLD, errorcode);
    if (rank == 0)
        printf("Start it\n");
    for (int i = 0; i < size; i++)
    {
        if (i == rank)
            continue;
        int buffer[2];
        buffer[0] = rank;
        buffer[1] = i;
        MPI_Status status;
        MPI_Send(buffer, 2, MPI_INT, i, 99, MPI_COMM_WORLD);
        MPI_Recv(buffer, 2, MPI_INT, i, 99, MPI_COMM_WORLD, &status);
        // if (buffer[0] == i && buffer[1] == rank)
        printf("%d, %d: %d to %d\n", rank, i, buffer[0], buffer[1]);
        // else
        // printf("miss it!");
    }
    MPI_Finalize();
    return 0;
}