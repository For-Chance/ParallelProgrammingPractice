/******************************************************************************
 * FILE: 7_19_recv_source_and_tag.c
 * DESCRIPTION:
 *   	receive source and tag.
 * RESULT:
 *
 * AUTHOR: Chance
 * CREATE TIME: 2022-07-29
 ******************************************************************************/

#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int rank, size, i, buf[1];
    MPI_Status status;
    MPI_Comm comm = MPI_COMM_WORLD;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_rank(comm, &size);
    if (rank == 0)
    {
        printf("start it\n");
        for (i = 0; i < 100 * (size - 1); i++)
        {
            MPI_Recv(buf, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, comm, &status);
            printf("Msg = %d, from %d with tag %d", buf[0], status.MPI_SOURCE, status.MPI_TAG);
        }
    }
    else
    {
        for (i = 0; i < 100; i++)
        {
            buf[0] = rank + i;
            MPI_Send(buf, 1, MPI_INT, 0, i, comm);
        }
    }
    MPI_Finalize();
    return 0;
}