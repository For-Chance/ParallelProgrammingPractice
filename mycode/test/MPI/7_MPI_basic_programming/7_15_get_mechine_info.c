/******************************************************************************
 * FILE: 7_15_get_mechine_info.c
 * DESCRIPTION:
 *   	Using MPI to get infomation of the machine.
 * RESULT:
 *
 * AUTHOR: Chance
 * CREATE TIME: 2022-07-28
 ******************************************************************************/
#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    char name[MPI_MAX_PROCESSOR_NAME];
    int resultlen, version, subversion;
    MPI_Init(&argc, &argv);
    MPI_Get_processor_name(name, &resultlen);
    MPI_Get_version(&version, &subversion);
    printf("Mechine name is %s, version is %d, subversion is %d\n", name, version, subversion);
    MPI_Finalize();
    return 0;
}