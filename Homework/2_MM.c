/******************************************************************************
 * FILE: 2_MM.c
 * DESCRIPTION:
 *   	Adding loop unrolling with the unrolling factor = 4 to homework 1.
 * RESULT:
 *      Set m, l and n 1000 every time.
 *      1. 8.050s - Run 1_MM.c with one thread.
 *      2. 1.825s - Run 1_MM.c with ten threads.
 *      3. 0.994s - Run 2_MM.c with ten threads and ikj loop.
 *      4. 0.656s - Run 2_MM.c with ten threads, ikj loop and unrolling i.
 *      5. 2.797s - Run 2_MM.c with ten threads, ikj loop and unrolling i,j.
 * AUTHOR: Chance
 * LAST REVISED: 2022-07-24
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

        // limit that m,l,n are divisible by 4
        if (m % 4 != 0 || l % 4 != 0 || n % 4 != 0)
            printf("Warning: Some of m, l, n are not divisible by 4!");
        m = m / 4 * 4;
        l = l / 4 * 4;
        n = n / 4 * 4;
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
    // printf("A:\n");
    // print_matrix(A, m, l);
    // printf("B:\n");
    // print_matrix(B, l, n);
    // printf("C:\n");
    // print_matrix(C, m, n);
    // printf("Initialize success!\n\n");

    double i0, i1, i2, i3, j0, j1, j2, j3;
    double tt = omp_get_wtime();
#pragma omp parallel for shared(A, B, C) private(i, j, k)
    for (i = 0; i < m; i += 4)
        for (k = 0; k < n; k++)
        {
            i0 = A[i][k];
            i1 = A[i + 1][k];
            i2 = A[i + 2][k];
            i3 = A[i + 3][k];

            for (j = 0; j < l; j += 4)
            {
                j0 = B[k][j];
                j1 = B[k][j + 1];
                j2 = B[k][j + 2];
                j3 = B[k][j + 3];

                C[i][j] += i0 * j0;
                C[i][j + 1] += i0 * j1;
                C[i][j + 2] += i0 * j2;
                C[i][j + 3] += i0 * j3;

                C[i + 1][j] += i1 * j0;
                C[i + 1][j + 1] += i1 * j1;
                C[i + 1][j + 2] += i1 * j2;
                C[i + 1][j + 3] += i1 * j3;

                C[i + 2][j] += i2 * j0;
                C[i + 2][j + 1] += i2 * j1;
                C[i + 2][j + 2] += i2 * j2;
                C[i + 2][j + 3] += i2 * j3;

                C[i + 3][j] += i3 * j0;
                C[i + 3][j + 1] += i3 * j1;
                C[i + 3][j + 2] += i3 * j2;
                C[i + 3][j + 3] += i3 * j3;
            }
        }

    tt = omp_get_wtime() - tt;
    printf("It takes %f seconds to finish the computation.\n\n", tt);
    // printf("result C:\n");
    // print_matrix(C, m, n);
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
