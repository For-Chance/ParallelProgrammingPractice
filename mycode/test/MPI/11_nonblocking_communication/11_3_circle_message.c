/******************************************************************************
 * FILE: 11_3_circle_message.c
 * DESCRIPTION:
 *   	Circle mssage using nonblocking message.
 * RESULT:
 *      基本的四种通信方式都有可能阻塞，而非阻塞通信从源头上杜绝了阻塞
 * AUTHOR: Chance
 * CREATE TIME: 2022-07-31
 ******************************************************************************/
#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    char sendmsg[100] = "asdfasdf", recvmsg[100] = "";
    MPI_Comm comm = MPI_COMM_WORLD;
    int myid, numprocs, dest, source;
    MPI_Request request1, request2;
    MPI_Status status1, status2;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(comm, &myid);
    MPI_Comm_size(comm, &numprocs);
    dest = myid + 1;
    source = myid - 1;
    if (myid == 0)
        source = numprocs - 1;
    if (myid == numprocs - 1)
        dest = 0;
    MPI_Isend(sendmsg, 100, MPI_CHAR, dest, 99, comm, &request1);
    MPI_Wait(&request1, &status1);
    MPI_Irecv(recvmsg, 100, MPI_CHAR, source, 99, comm, &request2);
    MPI_Wait(&request2, &status2);

    // MPI_Send(sendmsg, 100, MPI_CHAR, dest, 99, comm);
    // MPI_Recv(recvmsg, 100, MPI_CHAR, source, 99, comm, &status2);

    // MPI_Ssend(sendmsg, 100, MPI_CHAR, dest, 99, comm);
    // MPI_Recv(recvmsg, 100, MPI_CHAR, source, 99, comm, &status2);

    printf("%d send to %d\n", status2.MPI_SOURCE, myid);
    MPI_Finalize();
    return 0;
}