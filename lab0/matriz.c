#include "matriz.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double** mat_cria (int m, int n)
{
  double** A = (double**) malloc(m*sizeof(double*));
  for (int i=0; i<m; ++i)
    A[i] = (double*) malloc(n*sizeof(double));
  return A;
}

void mat_libera (int m, double** A)
{
  for (int i=0; i<m; ++i)
    free(A[i]);
  free(A);
}
  
void mat_imprime (int m, int n, double** A)
{
  for (int i=0; i<m; ++i) {
    for (int j=0; j<n; ++j) {
      printf("%.16g  ", A[i][j]);
    }
    printf("\n");
  }
}

// lab0 (2) //////////////////////////////////////////
void mat_transposta(int m, int n, double** A, double** T)
{
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      T[i][j] = A[j][i];
    }
  }
  
}

void mat_multv(int m, int n, double** A, double* v, double* w)
{
  for (int i = 0; i < m; i++)
  {
    double temp = 0.0;
    for (int j = 0; j < n; j++)
    {
        temp += A[i][j] * v[j];
    }
    w[i] = temp;
  }
  
}

void mat_multm(int m, int n, int q, double** A, double** B, double** C)
{
  for (int i = 0; i < m; i++)
  {
    for (int j = 0; j < q; j++)
    {
      double temp = 0.0;
      for (int k = 0; k < n; k++)
      {
          temp += A[i][k] * B[k][j];
      }
      C[i][j] = temp;
    }
  }
}