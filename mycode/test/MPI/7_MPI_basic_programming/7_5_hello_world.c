/******************************************************************************
 * FILE: 7_5_hello_world.c
 * DESCRIPTION:
 *   	Hello MPI!
 * RESULT:
 *
 * AUTHOR: Chance
 * CREATE TIME: 2022-07-28
 ******************************************************************************/
#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int myid, numprocs, namelen;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Get_processor_name(processor_name, &namelen);
    printf("Hello World! Process %d of %d on %s\n", myid, numprocs, processor_name);
    MPI_Finalize();
    return 0;
}