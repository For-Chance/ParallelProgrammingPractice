/******************************************************************************
 * FILE: 7_14_test_send_message.c
 * DESCRIPTION:
 *   	Test the efficiency of sending message.
 * RESULT:
 *
 * AUTHOR: Chance
 * CREATE TIME: 2022-07-28
 ******************************************************************************/
#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int size, rank, i, m, n;
    int xx = 300000;
    double t, t1, t2, tick;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (size != 2)
    {
        printf("This program must run with 2 processors\n");
        MPI_Abort(MPI_COMM_WORLD, 99);
    }
    m = rank;
    if (rank == 0)
    {
        t1 = MPI_Wtime();
        for (i = 0; i < xx; i++)
        {
            MPI_Send(&m, 4, MPI_BYTE, 1, i, MPI_COMM_WORLD);
            MPI_Recv(&n, 4, MPI_BYTE, 1, i, MPI_COMM_WORLD, &status);
        }
        t2 = MPI_Wtime();
        t = t2 - t1;
        tick = MPI_Wtick(); // 时钟频率
    }
    if (rank == 1)
    {
        for (i = 0; i < xx; i++)
        {
            MPI_Recv(&m, 4, MPI_BYTE, 0, i, MPI_COMM_WORLD, &status);
            MPI_Send(&m, 4, MPI_BYTE, 0, i, MPI_COMM_WORLD);
        }
    }
    if (rank == 0)
        printf("Total time for send & recv is %f, MPI_Wtick is %f\n", t, tick);
    MPI_Finalize();
    return 0;
}