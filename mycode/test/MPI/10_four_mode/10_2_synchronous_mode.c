/******************************************************************************
 * FILE: 10_2_synchronous_mode.c
 * DESCRIPTION:
 *   	Synchronous mode.
 * RESULT:
 *      标准模式下，发送数量不超过缓冲区的话，没有接收依旧能够继续进程
 *      同步模式下则是会被阻塞
 * AUTHOR: Chance
 * CREATE TIME: 2022-07-30
 ******************************************************************************/
#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int rank, act_size = 0, np, buffer[10], count1, count2;
    MPI_Status status1, status2;
    MPI_Init(&argc, &argv);
    MPI_Comm comm = MPI_COMM_WORLD;
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &np);
    // if (np != 2)
    //     MPI_Abort(comm, 1);
    act_size = 5; // 最大消息长度
    if (rank == 0)
    {
        MPI_Ssend(buffer, act_size, MPI_INT, 1, 1, comm);
        printf("MPI_Ssend %d data, tag = 1\n", act_size); // 能打印就说明发送成功
        act_size = 4;
        MPI_Ssend(buffer, act_size, MPI_INT, 1, 2, comm);
        printf("MPI_Ssend %d data, tag = 2\n", act_size);
    }
    else if (rank == 1)
    {
        MPI_Recv(buffer, act_size, MPI_INT, 0, 1, comm, &status1);
        MPI_Recv(buffer, act_size, MPI_INT, 0, 2, comm, &status2);
        MPI_Get_count(&status1, MPI_INT, &count1); // 拿到发送数据的数量
        printf("receive %d data, tag = %d\n", count1, status1.MPI_TAG);
        MPI_Get_count(&status2, MPI_INT, &count2);
        printf("receive %d data, tag = %d\n", count2, status2.MPI_TAG);
    }
    MPI_Finalize();
    return 0;
}