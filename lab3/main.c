#include "sistlinear.h"
#include "matriz.h"
#include "vetor.h"
#include <stdio.h>
#include <stdlib.h>

static void avaliagauss (int n, double **A, double* b)
{
  // adicione aqui a chamada de gauss e possiveis prints para debug
  // não esqueca de alocar dinamicamente o vetor x que ira receber a solucao

  double* x = vet_cria(n);
  gauss(n, A, b, x);
  printf("Resultado de X:\n");
  vet_imprime(n, x);
  vet_libera(x);
}

static void trocalinha (int n, double **A, double* b, int L0, int L1)
{
  for (int i = 0; i < n; ++i) {
	double AvL0 = A[L0][i];
	A[L0][i] = A[L1][i];
	A[L1][i] = AvL0;
  }
  double bvL0 = b[L0];
  b[L0] = b[L1];
  b[L1] = bvL0;
}

int main (void)
{
  {
    double** A1 = mat_cria(3,3);
    A1[0][0] =  1; A1[0][1] = -1; A1[0][2] = 0;
    A1[1][0] = -1; A1[1][1] =  2; A1[1][2] = 1;
    A1[2][0] =  0; A1[2][1] =  1; A1[2][2] = 2;
    double* B1 = vet_cria(3);
    B1[0] = 0; B1[1] = 2; B1[2] = 3;
    printf("\n\n---Sistema 1---\n");

    printf("Matrix A1:\n");
    mat_imprime(3, 3, A1);
    printf("Vector B1:\n");
    vet_imprime(3, B1);
    printf("\n");

    avaliagauss(3, A1, B1);

    mat_libera(3, A1);
    vet_libera(B1);
  }

  {
    double** A2 = mat_cria(6,6);
    A2[0][0] =   3; A2[0][1] =  -1; A2[0][2] =  0; A2[0][3] =  0; A2[0][4] =   0; A2[0][5] = 0.5;
    A2[1][0] =  -1; A2[1][1] =   3; A2[1][2] = -1; A2[1][3] =  0; A2[1][4] = 0.5; A2[1][5] =   0;
    A2[2][0] =   0; A2[2][1] =  -1; A2[2][2] =  3; A2[2][3] = -1; A2[2][4] =   0; A2[2][5] =   0;
    A2[3][0] =   0; A2[3][1] =   0; A2[3][2] = -1; A2[3][3] =  3; A2[3][4] =  -1; A2[3][5] =   0;
    A2[4][0] =   0; A2[4][1] = 0.5; A2[4][2] =  0; A2[4][3] = -1; A2[4][4] =   3; A2[4][5] =  -1;
    A2[5][0] = 0.5; A2[5][1] =   0; A2[5][2] =  0; A2[5][3] =  0; A2[5][4] =  -1; A2[5][5] =   3;
    double* B2 = vet_cria(6);
    B2[0] = 2.5; B2[1] = 1.5; B2[2] = 1; B2[3] = 1; B2[4] = 1.5; B2[5] = 2.5;
    printf("\n\n---Sistema 2---\n");
    
    printf("Matrix A1:\n");
    mat_imprime(6, 6, A2);
    printf("Vector B1:\n");
    vet_imprime(6, B2);
    printf("\n");

    avaliagauss(6, A2, B2);

	  mat_libera(6, A2);
    vet_libera(B2);
  }

  {
    double** A = mat_cria(2,2);
    A[0][0] = 1;      A[0][1] = 1;
    A[1][0] = 1.0001; A[1][1] = 1;
    double b[2] = {2,2.0001};
    printf("\n\n---Sistema 3---\n");
    
    printf("Matrix A1:\n");
    mat_imprime(2, 2, A);
    printf("Vector B1:\n");
    vet_imprime(2, b);
    printf("\n");

    avaliagauss(2, A, b);

    mat_libera(2, A);
  }
  
  {
    double** A = mat_cria(2,2);
    A[0][0] = -2; A[0][1] = 1;
    A[1][0] =  1; A[1][1] = 2;
    double b[2] = {2,3};

    printf("\n\n---Sistema 4---\n");
    
    printf("Matrix A1:\n");
    mat_imprime(2, 2, A);
    printf("Vector B1:\n");
    vet_imprime(2, b);
    printf("\n");

    avaliagauss(2, A, b);
    
    mat_libera(2, A);
  }

  {
    double** A2 = mat_cria(6,6);
    A2[0][0] =   3; A2[0][1] =  -1; A2[0][2] =  0; A2[0][3] =  0; A2[0][4] =   0; A2[0][5] = 0.5;
    A2[1][0] =  -1; A2[1][1] =   3; A2[1][2] = -1; A2[1][3] =  0; A2[1][4] = 0.5; A2[1][5] =   0;
    A2[2][0] =   0; A2[2][1] =  -1; A2[2][2] =  3; A2[2][3] = -1; A2[2][4] =   0; A2[2][5] =   0;
    A2[3][0] =   0; A2[3][1] =   0; A2[3][2] = -1; A2[3][3] =  3; A2[3][4] =  -1; A2[3][5] =   0;
    A2[4][0] =   0; A2[4][1] = 0.5; A2[4][2] =  0; A2[4][3] = -1; A2[4][4] =   3; A2[4][5] =  -1;
    A2[5][0] = 0.5; A2[5][1] =   0; A2[5][2] =  0; A2[5][3] =  0; A2[5][4] =  -1; A2[5][5] =   3;
    double* B2 = vet_cria(6);
    B2[0] = 2.5; B2[1] = 1.5; B2[2] = 1; B2[3] = 1; B2[4] = 1.5; B2[5] = 2.5;
	  trocalinha(6, A2, B2, 0, 2);
	  trocalinha(6, A2, B2, 1, 4);
    
    printf("\n\n---Sistema 5---\n");
    
    printf("Matrix A1:\n");
    mat_imprime(6, 6, A2);
    printf("Vector B1:\n");
    vet_imprime(6, B2);
    printf("\n");

    avaliagauss(6, A2, B2);
	  mat_libera(6, A2);
    vet_libera(B2);
  }

  {
    double** A = mat_cria(3,3);
    A[0][0] = -3; A[0][1] =  1; A[0][2] =  1;
    A[1][0] =  2; A[1][1] =  1; A[1][2] = -2;
    A[2][0] =  1; A[2][1] =  2; A[2][2] = -1;
    double* b = vet_cria(3);
    b[0] = -6; b[1] = 3; b[2] = 3;

    printf("\n\n---Sistema 6---\n");
    
    printf("Matrix A1:\n");
    mat_imprime(3, 3, A);
    printf("Vector B1:\n");
    vet_imprime(3, b);
    printf("\n");

    avaliagauss(3, A, b);
    mat_libera(3, A);
    vet_libera(b);
  }

  {
    double** A = mat_cria(3,3);
    A[0][0] = -3; A[0][1] =  1; A[0][2] =  1;
    A[1][0] =  2; A[1][1] =  1; A[1][2] = -2;
    A[2][0] =  1; A[2][1] =  2; A[2][2] = -1;
    double* b = vet_cria(3);
    b[0] = -6; b[1] = 3; b[2] = 3;
    trocalinha(3, A, b, 0, 2);

    printf("\n\n---Sistema 7---\n");
    
    printf("Matrix A1:\n");
    mat_imprime(3, 3, A);
    printf("Vector B1:\n");
    vet_imprime(3, b);
    printf("\n");

    avaliagauss(3, A, b);
    mat_libera(3, A);
    vet_libera(b);
  }

  {
    double** A = mat_cria(2,2);
    A[0][0] = 1e-17; A[0][1] = 1;
    A[1][0] =     1; A[1][1] = 2;
    double b[2] = {1,4};

    printf("\n\n---Sistema 8---\n");
    
    printf("Matrix A1:\n");
    mat_imprime(2, 2, A);
    printf("Vector B1:\n");
    vet_imprime(2, b);
    printf("\n");

    avaliagauss(2,A,b);
    mat_libera(2, A);
  }

  return 0;
}

