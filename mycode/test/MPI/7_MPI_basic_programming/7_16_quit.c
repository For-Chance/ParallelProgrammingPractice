/******************************************************************************
 * FILE: 7_16_quit.c
 * DESCRIPTION:
 *   	Test whether has been initialized and quit with error.
 * RESULT:
 *
 * AUTHOR: Chance
 * CREATE TIME: 2022-07-29
 ******************************************************************************/
#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int flag;
    // MPI_Init(&argc, &argv);
    MPI_Initialized(&flag);
    int errorcode;
    int node, size;
    if (flag)
    {
        printf("Has been initialized!\n");
        MPI_Abort(MPI_COMM_WORLD, errorcode);
    }
    else
    {
        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &node);
        MPI_Comm_size(MPI_COMM_WORLD, &size);
        if (size != 4)
            MPI_Abort(MPI_COMM_WORLD, errorcode);
        printf("id = %d, size = %d\n", node, size);
        MPI_Finalize();
    }
    return 0;
}