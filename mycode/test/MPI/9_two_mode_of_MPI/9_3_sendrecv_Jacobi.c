/******************************************************************************
 * FILE: 9_3_sendrecv_Jacobi.c
 * DESCRIPTION:
 *   	Using programming for Jacobi iteration using MPI_SENDRECV.
 * RESULT:
 *      和9.2运行时间差不多
 * AUTHOR: Chance
 * CREATE TIME: 2022-07-29
 ******************************************************************************/
#include <mpi.h>
#include <stdio.h>
#define N 500
#define SIZE N / 4
#define T 100
void print_myRows(int myid, double myRows[][N]);
int main(int argc, char *argv[])
{
    double myRows[SIZE + 2][N], myRows2[SIZE + 2][N];
    int myid, nproc, i, j, step, r_begin, r_end;
    MPI_Status status;
    MPI_Comm comm = MPI_COMM_WORLD;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(comm, &myid);
    MPI_Comm_size(comm, &nproc);
    for (i = 0; i < SIZE + 2; i++)
        for (j = 0; j < N; j++)
            myRows[i][j] = myRows2[i][j] = 0.0;
    if (myid == 0)
    {
        for (j = 0; j < N; j++)
            myRows[1][j] = 8.0;
    }
    if (myid == 3)
    {
        for (j = 0; j < N; j++)
            myRows[SIZE][j] = 8.0;
    }
    for (i = 1; i < SIZE + 1; i++)
        myRows[i][0] = myRows[i][N - 1] = 8.0;
    // 迭代
    MPI_Barrier(comm);
    double tt = MPI_Wtime();
    for (step = 0; step < T; step++)
    {
        if (myid == 0) // 向下发送
            MPI_Send(&myRows[SIZE][0], N, MPI_DOUBLE, 1, 0, comm);
        if (myid == nproc - 1) // 从上接收
            MPI_Recv(&myRows[0][0], N, MPI_DOUBLE, myid - 1, 0, comm, &status);
        if (myid > 0 && myid < nproc - 1) // 向下发送并且从上接收
            MPI_Sendrecv(&myRows[SIZE][0], N, MPI_DOUBLE, myid + 1, 0, &myRows[0][0], N, MPI_DOUBLE, myid - 1, 0, comm, &status);
        if (myid == 0) // 从下接收
            MPI_Recv(&myRows[SIZE + 1][0], N, MPI_DOUBLE, 1, 0, comm, &status);
        if (myid == nproc - 1)
            MPI_Send(&myRows[1][0], N, MPI_DOUBLE, myid - 1, 0, comm);
        if (myid > 0 && myid < nproc - 1) // 向上发送并且从下接收
            MPI_Sendrecv(&myRows[1][0], N, MPI_DOUBLE, myid - 1, 0, &myRows[SIZE + 1][0], N, MPI_DOUBLE, myid + 1, 0, comm, &status);
        // 注意 0 线程不往上发和收，线程 3 不往下发和收，否则会造成死锁
        // 计算
        // 注意要计算的起始和结束行
        r_begin = (0 == myid) ? 2 : 1;
        r_end = (3 == myid) ? SIZE - 1 : SIZE;
        for (i = r_begin; i <= r_end; i++)
            for (j = 1; j < N - 1; j++)
                myRows2[i][j] = 0.25 * (myRows[i][j - 1] + myRows[i][j + 1] + myRows[i - 1][j] + myRows[i + 1][j]);
        for (i = r_begin; i <= r_end; i++)
            for (j = 1; j < N - 1; j++)
                myRows[i][j] = myRows2[i][j];
    }
    // print_myRows(myid, myRows);
    MPI_Barrier(comm);
    tt = MPI_Wtime() - tt;
    printf("cost time = %f\n", tt);
    MPI_Finalize();
    return 0;
}

void print_myRows(int myid, double myRows[][N])
{
    int i, j;
    printf("Result in process %d:\n", myid);
    for (i = 0; i < SIZE + 2; i++)
    {
        for (j = 0; j < N; j++)
            printf("%.3f\t", myRows[i][j]);
        printf("\n");
    }
}