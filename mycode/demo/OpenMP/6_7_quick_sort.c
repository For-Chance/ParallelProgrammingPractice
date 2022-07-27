/******************************************************************************
 * FILE: 6_7_quick_sort.c
 * DESCRIPTION:
 *   	Demo of parallel programming for quick sort.
 * RESULT:
 *      Some errors happened!
 * AUTHOR: Chance
 * CREATE TIME: 2022-07-27
 ******************************************************************************/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int count = 0; // 比较次数
const int len = 50000;
const int short_len = 25000;

void swap(int &a, int &b)
{
    int t;
    t = a;
    a = b;
    b = t;
}

int randint(int a, int b)
{
    int e = 0;
    e = b - a;
    return rand() % e + a;
}

void quicksort(int *A, int l, int r)
{
    int i, m, k;
    if (l >= r)
        return;
    // 选择第一个作为哨兵
    m = l;
    for (i = l + 1; i <= r; i++)
        if (A[i] < A[l])
            swap(A[++m], A[i]);
    swap(A[l], A[m]);
    count += r - l;
    quicksort(A, l, m - 1);
    quicksort(A, m + 1, r);
}

int main(int argc, char *argv[])
{
    omp_set_num_threads(10);
    int j = len, k = 0, i = 0;
    int m = 0, n = 0;
    clock_t begin, end;
    double cost;
    srand((unsigned)time(NULL));
    int B[len], C[short_len], D[short_len];

// 初始化
#pragma omp parallel default(none) shared(B, len, j) private(i)
    {
#pragma omp for
        for (i = 0; i < len; i++)
            B[i] = j--;
    }

    begin = clock();
#pragma omp prallel default(none) shared(B, C, D, short_len) private(i)
    {
#pragma omp for
        for (i = 0; i < short_len; i++)
        {
            C[i] = B[i];
            D[i] = D[i + 25000];
        }
    }
#pragma omp parallel default(none) shared(C, D, short_len) private(i)
    {
#pragma omp parallel sections
        {
#pragma omp section
            quicksort(C, 0, short_len - 1);
#pragma omp section
            quicksort(D, 0, short_len - 1);
        }
    }
    printf("\n");
    for (; k < len; k++)
    {
        if (m < short_len && n < short_len)
        {
            if (C[n] <= D[m])
            {
                B[k] = C[n];
                n++;
            }
        }
        else
        {
            B[k] = D[m];
            m++;
        }
        if (m == short_len || n == short_len)
        {
            if (m == short_len)
                B[k] = D[m];
            else
                B[k] = C[n - 1];
            k += 1;
            break;
        }
    }
    if (n < short_len)
    {
        int tem = short_len - n;
        for (int p = 0; p < tem; p++)
        {
            B[k] = C[n];
            n++;
            k++;
        }
    }
    else if (m < short_len)
    {
        int tem = short_len - m;
        for (int q = 0; q < tem; q++)
        {
            B[k] = D[m];
            m++;
            k++;
        }
    }
    end = clock();
    cost = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%lf seconds/n", cost);
    system("pause");
    return 0;
}