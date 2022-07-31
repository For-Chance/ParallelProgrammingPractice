/******************************************************************************
 * FILE: 12_2_gather.c
 * DESCRIPTION:
 *   	Gather from boardcast using MPI_GATHER
 * RESULT:
 *
 * AUTHOR: Chance
 * CREATE TIME: 2022-07-31
 ******************************************************************************/
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int myid, numprocs, sendArray[10], *recvArray;
    MPI_Comm comm = MPI_COMM_WORLD;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(comm, &myid);
    MPI_Comm_size(comm, &numprocs);
    recvArray = (int *)malloc(numprocs * 10 * sizeof(int));
    for (int i = 0; i < 10; i++)
        sendArray[i] = myid * 10 + i;
    MPI_Gather(sendArray, 10, MPI_INT, recvArray, 10, MPI_INT, 0, comm);
    if (myid == 0)
    {
        for (int i = 0; i < 10 * numprocs; i++)
            printf("myid = %d, i = %d, value = %d\n", myid, i, recvArray[i]);
    }
    free(recvArray);
    MPI_Finalize();
    return 0;
}