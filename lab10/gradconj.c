#include "gradconj.h"
#include "matriz.h"

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

double norma2(int n, double *rk)
{
    double norma2 = 0.0;
    for (int i = 0; i < n; i++)
    {
        norma2 += rk[i] * rk[i];
    }
    norma2 = sqrt(norma2);
    return norma2;
}

int gradconj (int n, double** A, double* b, double* x, double tol){
    double *x0, *r0, *d0, *z0, *Ax0, *M;
    x0  = (double*)malloc(sizeof(double) * n); for (int i = 0; i < n; i++) {x0[i] = 0.0;}
    r0  = (double*)malloc(sizeof(double) * n); for (int i = 0; i < n; i++) {r0[i] = 0.0;}
    d0  = (double*)malloc(sizeof(double) * n); for (int i = 0; i < n; i++) {d0[i] = 0.0;}
    z0  = (double*)malloc(sizeof(double) * n); for (int i = 0; i < n; i++) {z0[i] = 0.0;}
    Ax0 = (double*)malloc(sizeof(double) * n); for (int i = 0; i < n; i++){Ax0[i] = 0.0;}

    for (int i = 0; i < n; i++)
    {
        x0[i] = x[i];
        for (int j = 0; j < n; j++)
        {
            Ax0[i] += A[i][j] * x0[j];
        }
        r0[i] = b[i] - Ax0[i];
        d0[i] = z0[i] = r0[i]; // M é a matriz identidade
    }

    double alfa = 0.0, alfaDeno = 0.0;
    double* alfaV = (double*)malloc(sizeof(double) * n);

    double *rNovo = (double*)malloc(sizeof(double) * n);
    double *zNovo = (double*)malloc(sizeof(double) * n);
    double beta = 0.0, betaDeno = 0.0;

    int it = n;
    for (int k = 0; k < n; k++)
    {
        printf("Iteração %d: \n", k);
        if (norma2(n, r0) < tol){
            it = k + 1;
            break;
        }
        
        for (int i = 0; i < n; i++)
        {
            alfa += r0[i] * z0[i];
        }
        mat_multv(n, n, A, d0, alfaV);
        for (int i = 0; i < n; i++)
        {
            alfaDeno += d0[i] * alfaV[i];
        }

        alfa = alfa / alfaDeno;

        for (int i = 0; i < n; i++)
        {
            x0[i] = x0[i] + alfa * d0[i];
            rNovo[i] = r0[i] - alfa * alfaV[i];
            zNovo[i] = r0[i]; // M é a matriz identidade
        }

        for (int i = 0; i < i; i++)
        {
            beta += rNovo[i] * zNovo[i];
            betaDeno += r0[i] * z0[i];
        }

        beta = beta / betaDeno;

        for (int i = 0; i < n; i++)
        {
            d0[i] = zNovo[i] + beta * d0[i];
        }


        alfa = 0.0, alfaDeno = 0.0;
        beta = 0.0, betaDeno = 0.0;
        for (int i = 0; i < n; i++)
        {
            alfaV[i] = 0.0;
            rNovo[i] = 0.0;
            zNovo[i] = 0.0;
        }
        
    }

    free(x0); free(r0); free(d0);
    free(z0); free(Ax0); free(alfaV);
    free(rNovo); free(zNovo);

    return it;
}

int gradconj_jacobi (int n, double** A, double* b, double* x, double tol){

}