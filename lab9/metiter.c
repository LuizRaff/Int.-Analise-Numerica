#include <stdio.h>
#include "metiter.h"
#include <math.h>
#include <stdlib.h>

double norma2(int n, double **A, double *x, double *b)
{
    // Calcula a norma 2 de || b - Ax ||
    double *AX = (double *)malloc(n * sizeof(double));
    for (int i = 0; i < n; i++)
    {
        AX[i] = 0.0;
        for (int j = 0; j < n; j++)
        {
            AX[i] += A[i][j] * x[j];
        }
        AX[i] = b[i] - AX[i];
    }

    double norma2 = 0.0;
    for (int i = 0; i < n; i++)
    {
        norma2 += AX[i] * AX[i];
    }
    norma2 = sqrt(norma2);
    free(AX);
    return norma2;
}

int gaussseidel(int n, double **A, double *b, double *x, double tol)
{
    int it = 0;
    double norma = norma2(n, A, x, b);
    while (norma > tol)
    {
        for (int i = 0; i < n; i++)
        {
            double sum1 = 0.0, sum2 = 0.0;

            for (int j = 0; j < i; j++)
                sum1 += A[i][j] * x[j];

            for (int j = i + 1; j < n; j++)
                sum2 += A[i][j] * x[j];

            x[i] = (b[i] - sum1 - sum2) / A[i][i];
        }
        it++;
        norma = norma2(n, A, x, b);
    }

    return it;
}

int sor_gaussseidel(int n, double **A, double *b, double *x, double tol, double w)
{
    int it = 0;
    double norma = norma2(n, A, x, b);
    while (norma > tol)
    {
        for (int i = 0; i < n; i++)
        {
            double sum1 = 0.0, sum2 = 0.0;

            for (int j = 0; j < i; j++)
                sum1 += A[i][j] * x[j];

            for (int j = i + 1; j < n; j++)
                sum2 += A[i][j] * x[j];

            double xtemp = x[i];
            x[i] = (b[i] - sum1 - sum2) / A[i][i];
            x[i] = (1 - w) * xtemp + (w * x[i]);
        }
        it++;
        norma = norma2(n, A, x, b);
    }

    return it;
}