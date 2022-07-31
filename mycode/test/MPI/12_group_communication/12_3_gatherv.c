/******************************************************************************
 * FILE: 12_3_gatherv.c
 * DESCRIPTION:
 *   	Master processor gather data from other processors using MPI_GATHERV.
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
    int i, myid, numproc, send_num, *sendarray, *rbuf, *displs, *rcounts, n;
    MPI_Comm comm = MPI_COMM_WORLD;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(comm, &myid);
    MPI_Comm_size(comm, &numproc);
    send_num = myid + 1; // 各个进程发给根进程的数据个数
    sendarray = (int *)malloc(send_num * sizeof(int));
    for (i = 0; i < send_num; i++)
        sendarray[i] = myid * 10 + i;
    if (myid == 0) // 根进程申请接收缓存区
    {
        rcounts = (int *)malloc(numproc * sizeof(int)); // 为接收数据个数申请内存空间
        displs = (int *)malloc(numproc * sizeof(int));  // 为偏移量申请内存空间
        rcounts[0] = 1;
        for (i = 1; i < numproc; i++)
        {
            rcounts[i] = i + 1;                             // 各个进程发送给根进程的数据个数为其进程号加一
            displs[i] = rcounts[i - 1] + displs[i - 1] + 2; // 相对于起始位置的偏移量
        }
        n = displs[numproc - 1] + rcounts[numproc - 1];
        rbuf = (int *)malloc(n * sizeof(int));
        for (i = 0; i < n; i++)
            rbuf[i] = -1;
    }
    else
    {
        rcounts = (int *)malloc(1 * sizeof(int));
        displs = (int *)malloc(1 * sizeof(int));
        rbuf = (int *)malloc(1 * sizeof(int));
    }
    for (i = 0; i < send_num; i++)
        printf("myid: %d, data id: %d, data: %d\n", myid, i, sendarray[i]);
    MPI_Gatherv(sendarray, send_num, MPI_INT, rbuf, rcounts, displs, MPI_INT, 0, comm);
    MPI_Barrier(comm);
    if (myid == 0)
    {
        for (i = 0; i < n; i++)
            printf("Process 0: i = %d, data = %d\n", i, rbuf[i]);
    }
    free(sendarray);
    free(rcounts);
    free(displs);
    free(rbuf);
    return 0;
}