#include "mmq.h"
#include "matriz.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.141592653589793

int main(void) {
    int m, n;
    double** A;
    double *b, *x, *Ax;
    double erro;

    // Primeiro sistema
    m = 5; n = 3;
    A = mat_cria(m, n);
    double tmp1[5][3] = {{3,-1,2},{4,1,0},{-3,2,1},{1,1,5},{-2,0,3}};
    b = malloc(m * sizeof(double)); x = malloc(n * sizeof(double));
    for (int i = 0; i < m; i++) {
        b[i] = (double[]){10,10,-5,15,0}[i];
        for (int j = 0; j < n; j++) A[i][j] = tmp1[i][j];
    }
    erro = mmq(m, n, A, b, x);
    for (int i = 0; i < n; i++)
        printf("x[%d] = %.6f\n", i, x[i]);
    printf("Ax:\n");
    Ax = malloc(m * sizeof(double));
    mat_multv(m, n, A, x, Ax);
    for (int i = 0; i < m; i++)
        printf("Ax[%d] = %.6f\n", i, Ax[i]);
    printf("Erro: %.5f\n", erro);
    free(Ax);
    mat_libera(m, A); free(b); free(x);

    printf("-------------------------\n");

    // Segundo sistema
    printf("solucao:\n");
    m = 5; n = 4;
    A = mat_cria(m, n);
    double tmp2[5][4] = {{4,2,3,0},{-2,3,-1,1},{1,3,-4,2},{1,0,1,-1},{3,1,3,-2}};
    b = malloc(m * sizeof(double)); x = malloc(n * sizeof(double));
    for (int i = 0; i < m; i++) {
        b[i] = (double[]){10,0,2,0,5}[i];
        for (int j = 0; j < n; j++) A[i][j] = tmp2[i][j];
    }
    erro = mmq(m, n, A, b, x);
    for (int i = 0; i < n; i++)
        printf("x[%d] = %.6f\n", i, x[i]);
    printf("Ax:\n");
    Ax = malloc(m * sizeof(double));
    mat_multv(m, n, A, x, Ax);
    for (int i = 0; i < m; i++)
        printf("Ax[%d] = %.6f\n", i, Ax[i]);
    printf("Erro: %.5f\n", erro);
    free(Ax);
    mat_libera(m, A); free(b); free(x);

    printf("-------------------------\n");
    // Ajustes de curva
    double pxs[3][4] = {{-1,0,1,2},{0,1,2,5},{1,3,4,6}};
    double pys[3][4] = {{1,0,0,-2},{0,3,3,6},{2,2,1,3}};
    for (int t = 0; t < 3; t++) {
        double a, b0, c0, d0;
        printf("parabola:\n");
        erro = ajuste_parabola(4, pxs[t], pys[t], &a, &b0, &c0);
        printf("Erro: %g\n", erro);
        printf("a = %g  b = %g  c = %g\n", a, b0, c0);
        printf("cubica:\n");
        erro = ajuste_cubica(4, pxs[t], pys[t], &a, &b0, &c0, &d0);
        printf("Erro: %g\n", erro);
        printf("a = %g  b = %g  c = %g  d = %g\n", a, b0, c0, d0);
        printf("-------------------------\n");
    }

    // Ajustes exponenciais
    {
        double px[7] = {1950,1955,1960,1965,1970,1975,1980};
        double py[7] = {53.05,73.04,98.31,139.78,193.48,260.20,320.39};
        double a, b0;
        printf("exponencial:\n");
        erro = ajuste_exponencial_exp(7, px, py, &a, &b0);
        printf("Erroln: %g\n", erro);
        printf("a = %g  b = %g\n", a, b0);
        printf("-------------------------\n");
    }
    {
        double px[7] = {0,5,10,15,20,25,30};
        double py[7] = {53.05,73.04,98.31,139.78,193.48,260.20,320.39};
        double a, b0;
        printf("exponencial:\n");
        erro = ajuste_exponencial_exp(7, px, py, &a, &b0);
        printf("Erroln: %g\n", erro);
        printf("a = %g  b = %g\n", a, b0);
    }

    return 0;
}
