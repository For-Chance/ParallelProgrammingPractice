/******************************************************************************
 * FILE: 10_1_standard_mode.c
 * DESCRIPTION:
 *   	Communication mode of buffered mode.
 * RESULT:
 *
 * AUTHOR: Chance
 * CREATE TIME: 2022-07-30
 ******************************************************************************/
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[])
{
    MPI_Comm comm = MPI_COMM_WORLD;
    int dest = 1, src = 0, tag = 1, rank, bufsize, s1, s2, s3;
    char *buf, msg1[7], msg3[17], rmsg1[64], rmsg3[64];
    double msg2[2], rmsg2[64];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(comm, &rank);
    MPI_Pack_size(7, MPI_CHAR, comm, &s1);           // 求取7个字符所占空间
    MPI_Pack_size(2, MPI_DOUBLE, comm, &s2);         // 求取2个双精度数所占的空间
    MPI_Pack_size(17, MPI_CHAR, comm, &s3);          // 求取17个字符所占空间
    bufsize = 3 * MPI_BSEND_OVERHEAD + s1 + s2 + s3; // 3次缓存发送所需的缓冲区大小
    buf = (char *)malloc(bufsize);                   // 申请缓冲区
    MPI_Buffer_attach(buf, bufsize);                 // 将所申请的缓冲区递交给MPI运行系统，倘若无此句，MPI_Bsend使用将会报错
    // 赋值
    strncpy_s(msg1, sizeof(msg1), "012345", 7);            // 字符串赋值
    strncpy_s(msg3, sizeof(msg3), "0123401234012341", 17); // 字符串赋值
    msg2[0] = 1.23;                                        // 双精度数组元素赋值
    msg2[1] = 3.21;                                        // 双精度数组元素赋值
    // 发送
    if (rank == src) // 进程0发送
    {
        MPI_Bsend(msg1, 7, MPI_CHAR, dest, tag, comm);
        MPI_Bsend(msg2, 2, MPI_DOUBLE, dest, tag, comm);
        MPI_Bsend(msg3, 17, MPI_CHAR, dest, tag, comm);
    }
    if (rank == dest) // 进程1接收，不设置执行状态
    {
        MPI_Recv(rmsg1, 7, MPI_CHAR, src, tag, comm, MPI_STATUS_IGNORE);
        MPI_Recv(rmsg2, 10, MPI_DOUBLE, src, tag, comm, MPI_STATUS_IGNORE);
        MPI_Recv(rmsg3, 17, MPI_CHAR, src, tag, comm, MPI_STATUS_IGNORE);
        // 检查是否接收成功
        // if (strcmp(rmsg1, msg1) != 0)
        printf("message 1 (%s) shoubld be (%s)\n", rmsg1, msg1);
        // if (rmsg2[0] != msg2[0] || rmsg2[1] != msg2[1])
        printf("message 2 (%f, %f) should be (%f, %f)\n", rmsg2[0], rmsg2[1], msg2[0], msg2[1]);
        // if (strcmp(rmsg3, msg3) != 0)
        printf("message 3 (%s) should be (%s)\n", rmsg3, msg3);
    }
    MPI_Buffer_detach(buf, &bufsize); // 收回缓存区
    free(buf);
    MPI_Finalize();
    return 0;
}