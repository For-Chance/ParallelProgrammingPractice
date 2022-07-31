/******************************************************************************
 * FILE: 12_1_bcast.c
 * DESCRIPTION:
 *   	Test bcast.
 * RESULT:
 *
 * AUTHOR: Chance
 * CREATE TIME: 2022-07-31
 ******************************************************************************/
#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int rank, value;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    value = (rank + 1) * 11;
    printf("Before broadcast, myid = %d, my value = %d\n", rank, value);
    MPI_Bcast(&value, 1, MPI_INT, 0, MPI_COMM_WORLD);
    printf("After broadcast, myid = %d, my value = %d\n", rank, value);
    MPI_Finalize();
    return 0;
}