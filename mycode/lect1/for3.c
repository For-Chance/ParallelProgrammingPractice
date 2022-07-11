/******************************************************************************
 * FILE: for3.c
 * DESCRIPTION:
 *      matrix-vector multiplication: b = Ax
 * AUTHOR: Chance
 * LAST REVISED: 2022-07-11
 ******************************************************************************/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_matrix(double **T, int rows, int cols);
void print_vector(double *T, int cols);

int main(int argc, char *argv[])
{
    double *a0, **a, *x, *b;
    int row, col;
    int tid, nthreads, i, k;

    if (argc == 4)
    {
        row = atoi(argv[1]);
        col = atoi(argv[2]);
        nthreads = atoi(argv[3]);

        printf("row = %d, col = %d\n", row, col);
        printf("nthreads = %d\n\n", nthreads);
    }
    else
    {
        printf("Usage: %s NRA NCA nthreads\n\n"
               " NRA: matrix a row length\n"
               " NCA: matrix a column (or x) length\n"
               " nthreads: the number of threads\n\n",
               argv[0]);
        return 1;
    }

    omp_set_num_threads(nthreads);

    a0 = (double *)malloc(row * col * sizeof(double));
    a = (double **)malloc(row * sizeof(double *));
    for (int i = 0; i < row; i++)
        a[i] = a0 + i * col;
    x = (double *)malloc(col * sizeof(double));
    b = (double *)malloc(row * sizeof(double));

    srand(time(0)); // seed

    // Initialize matrix and vectors
    for (i = 0; i < row; i++)
        for (k = 0; k < col; k++)
            a[i][k] = (double)rand() / RAND_MAX;
    printf("a:\n");
    print_matrix(a, row, col);
    for (i = 0; i < col; i++)
        x[i] = (double)rand() / RAND_MAX;
    printf("x:\n");
    print_vector(x, col);
    for (i = 0; i < row; i++)
        b[i] = 0.0;
    printf("b:\n");
    print_vector(b, col);

    double tt = omp_get_wtime();
#pragma omp parallel for shared(a, b, x) private(i, k)
    for (i = 0; i < row; i++)
        for (k = 0; k < col; k++)
            b[i] += a[i][k] * x[k];
    tt = omp_get_wtime() - tt;
    printf("It takes %f seconds to finish the computation.\n\n", tt);
    printf("result:\n");
    print_vector(b, row);
    return 0;
}

void print_matrix(double **T, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            printf("%.2f  ", T[i][j]);
        printf("\n");
    }
    printf("\n\n");
    return;
}

void print_vector(double *T, int cols)
{
    for (int i = 0; i < cols; i++)
        printf("%.2f  ", T[i]);
    printf("\n\n");
    return;
}