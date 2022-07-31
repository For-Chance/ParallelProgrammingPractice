/******************************************************************************
 * FILE: 10_3_ready_mode.c
 * DESCRIPTION:
 *   	Ready mode.
 * RESULT:
 *
 * AUTHOR: Chance
 * CREATE TIME: 2022-07-30
 ******************************************************************************/
#include <mpi.h>
#include <stdio.h>
void test_rsend();
int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);
    test_rsend();
    MPI_Finalize();
    return 0;
}

void test_rsend()
{
    int rank, size, count = 500, x1;
    double send_buf[2000], recv_buf[2000];
    MPI_Status status;
    MPI_Comm comm = MPI_COMM_WORLD;
    MPI_Request request;
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &size);
    // if(size != 2)
    //     MPI_Abort(comm, 1);
    if (rank == 0)
        printf("Rsend Test\n");
    if (rank == 0)
    {
        MPI_Recv(&x1, 0, MPI_INT, 1, 12, comm, &status);
        printf("Process %d post Ready send\n", rank);
        MPI_Rsend(send_buf, count, MPI_DOUBLE, 1, 12, comm);
    }
    else if (rank == 1)
    {
        printf("Process %d post a receive call\n", rank);
        MPI_Irecv(recv_buf, count, MPI_DOUBLE, 0, 12, comm, &request);
        MPI_Send(&x1, 0, MPI_INT, 0, 12, comm);
        MPI_Wait(&request, &status);
        printf("Process %d Receive Rsend message from %d\n", rank, status.MPI_SOURCE);
    }
}