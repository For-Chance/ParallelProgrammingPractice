/******************************************************************************
 * FILE: 11_4_cancel_nonblocking_communication.c
 * DESCRIPTION:
 *   	Cancel nonblocking communication.
 * RESULT:
 *
 * AUTHOR: Chance
 * CREATE TIME: 2022-07-31
 ******************************************************************************/
#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int rank, size, sbuf[1], rbuf[1], flag;
    MPI_Request request;
    MPI_Status status;
    MPI_Comm comm = MPI_COMM_WORLD;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &size);
    if (rank == 0)
        MPI_Send(sbuf, 1, MPI_INT, 1, 99, comm);
    else if (rank == 1)
    {
        MPI_Irecv(rbuf, 1, MPI_INT, 0, 99, comm, &request);
        MPI_Cancel(&request);
        MPI_Wait(&request, &status);
        MPI_Test_cancelled(&status, &flag);
        if (flag)
            MPI_Irecv(rbuf, 1, MPI_INT, 0, 99, comm, &request);
    }
    MPI_Finalize();
    return 0;
}