/******************************************************************************
 * FILE: 1_Matrix-Matrix_Multiplication.c
 * DESCRIPTION:
 *   	Matrix-Matrix Multiplication: C = AB
 * AUTHOR: Chance
 * LAST REVISED: 2022-07-11
 ******************************************************************************/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double **allocate_matrix(double **T, int row, int col);
void print_matrix(double **T, int rows, int cols);
double **initialize_matrix(double **T, int row, int col, int isZero);

int main(int argc, char *argv[])
{
    double **A, **B, **C;
    int m, l, n;
    int tid, nthreads, i, j, k;

    if (argc == 5)
    {
        m = atoi(argv[1]);
        l = atoi(argv[2]);
        n = atoi(argv[3]);
        nthreads = atoi(argv[4]);

        printf("m = %d, l = %d, n = %d\n", m, l, n);
        printf("nthreads = %d\n\n", nthreads);
    }
    else
    {
        printf("Usage: %s m l n threads\n"
               " m: matrix A row length\n"
               " l: matrix A column  length and matrix B row length\n"
               " n: matrix B column length"
               " nthreads: the number of threads\n\n",
               argv[0]);
        return 1;
    }

    omp_set_num_threads(nthreads);

    A = allocate_matrix(A, m, l);
    B = allocate_matrix(B, l, n);
    C = allocate_matrix(C, m, n);
    srand(time(0));
    A = initialize_matrix(A, m, l, 0);
    B = initialize_matrix(B, l, n, 0);
    C = initialize_matrix(C, m, n, 1);
    printf("A:\n");
    print_matrix(A, m, l);
    printf("B:\n");
    print_matrix(B, l, n);
    printf("C:\n");
    print_matrix(C, m, n);
    printf("Initialize success!\n\n");

    double tt = omp_get_wtime();
#pragma omp parallel for shared(A, B, C) private(i, j, k)
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            for (k = 0; k < l; k++)
                C[i][j] += A[i][k] + B[k][j];
    tt = omp_get_wtime() - tt;
    printf("It takes %f seconds to finish the computation.\n\n", tt);
    printf("result C:\n");
    print_matrix(C, m, n);
    return 0;
}

double **allocate_matrix(double **T, int row, int col)
{
    T = (double **)malloc(row * sizeof(double *));
    for (int i = 0; i < row; i++)
        T[i] = (double *)malloc(col * sizeof(double));
    return T;
}

void print_matrix(double **T, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            printf("%.2f  ", T[i][j]);
        printf("\n");
    }
    printf("\n");
    return;
}

double **initialize_matrix(double **T, int row, int col, int isZero)
{
    int i, k;
    if (isZero == 0)
    {
        for (i = 0; i < row; i++)
            for (k = 0; k < col; k++)
                T[i][k] = (double)rand() / RAND_MAX;
    }
    else
    {
        for (i = 0; i < row; i++)
            for (k = 0; k < col; k++)
                T[i][k] = 0.0;
    }
    return T;
}
