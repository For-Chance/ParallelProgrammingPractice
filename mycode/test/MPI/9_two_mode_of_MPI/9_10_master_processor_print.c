/******************************************************************************
 * FILE: 9_10_master_processor_print.c
 * DESCRIPTION:
 *   	master processor print infomation.
 * RESULT:
 *
 * AUTHOR: Chance
 * CREATE TIME: 2022-07-30
 ******************************************************************************/
#include <mpi.h>
#include <stdio.h>
#include <string.h>
#define MSG_EXIT 1
#define MSG_PRINT_ORDERED 2   // 定义按续打印标识
#define MSG_PRINT_UNORDERED 3 // 定义乱序打印标识
int master_io(void);
int slave_io(void);
int main(int argc, char *argv[])
{
    int rank, size;
    MPI_Comm comm = MPI_COMM_WORLD;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &size);
    if (rank == 0)
        master_io();
    else
        slave_io();
    MPI_Finalize();
    return 0;
}

int master_io()
{
    int i, j, size, nslave, firstmsg;
    char buf[256], buf2[256];
    MPI_Status status;
    MPI_Comm comm = MPI_COMM_WORLD;
    MPI_Comm_size(comm, &size);
    nslave = size - 1; // 从进程数
    while (nslave > 0)
    {
        MPI_Recv(buf, 256, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, comm, &status);
        switch (status.MPI_TAG)
        {
        case MSG_EXIT:
            printf("processor (%d) exit!\n", status.MPI_SOURCE);
            nslave--;
            break;

        case MSG_PRINT_UNORDERED:
            fputs(buf, stdout); // 直接打印
            break;

        case MSG_PRINT_ORDERED: // 先继续接收再打印
            firstmsg = status.MPI_SOURCE;
            for (i = 1; i < size; i++)
            {
                if (i == firstmsg)
                    fputs(buf, stdout);
                else
                {
                    MPI_Recv(buf2, 256, MPI_CHAR, i, MSG_PRINT_ORDERED, comm, &status);
                    fputs(buf2, stdout);
                }
            }
        }
    }
}

int slave_io(void)
{
    char buf[256];
    int rank;
    MPI_Comm comm = MPI_COMM_WORLD;
    MPI_Comm_rank(comm, &rank);
    sprintf(buf, "Hello from slave %d ordered print\n", rank);
    // 先发送有序打印消息
    MPI_Send(buf, strlen(buf) + 1, MPI_CHAR, 0, MSG_PRINT_ORDERED, comm);
    sprintf(buf, "Goodbye from salve %d, ordered print\n", rank);
    MPI_Send(buf, strlen(buf) + 1, MPI_CHAR, 0, MSG_PRINT_ORDERED, comm);
    sprintf(buf, "I'm exiting (%d), unordered print\n", rank);
    MPI_Send(buf, strlen(buf) + 1, MPI_CHAR, 0, MSG_PRINT_UNORDERED, comm);
    MPI_Send(buf, 0, MPI_CHAR, 0, MSG_EXIT, MPI_COMM_WORLD);
}