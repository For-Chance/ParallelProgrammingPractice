/******************************************************************************
 * FILE: 7_6_send_message.c
 * DESCRIPTION:
 *   	Demo of using MPI to send message.
 * RESULT:
 *
 * AUTHOR: Chance
 * CREATE TIME: 2022-07-28
 ******************************************************************************/
#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char message[20];
    int myrank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank); // tid
    if (myrank == 0)
    {
        strcpy(message, "Hello, process 1");
        MPI_Send(message, strlen(message), MPI_CHAR, 1, 99, MPI_COMM_WORLD);
    }
    if (myrank == 1)
    {
        MPI_Status status;
        MPI_Recv(message, 20, MPI_CHAR, 0, 99, MPI_COMM_WORLD, &status);
        printf("received :%s, status :%d", message, status);
    }
    MPI_Finalize();
    return 0;
}