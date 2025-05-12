#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "mmq.h"
#include "matriz.h"
#include "sistlinear.h"   
#include "vetor.h"        

double mmq(int m, int n, double** A, double* b, double* x) {
    // Alocar At, AtA e Atb
    double** At   = mat_cria(n, m);
    double** AtA  = mat_cria(n, n);
    double*  Atb  = vet_cria(n);

    // At = A^T
    mat_transposta(m, n, A, At);
    // AtA = At * A (n x n)
    mat_multm(n, m, n, At, A, AtA);
    // Atb = At * b
    mat_multv(n, m, At, b, Atb);

    // Resolver sistema AtA * x = Atb via Gauss
    gauss(n, AtA, Atb, x);

    // Liberar At, AtA e Atb
    mat_libera(n, At);
    mat_libera(n, AtA);
    vet_libera(Atb);

    // Calcular norma-2 do residual r = b - A x
    double* r = vet_cria(m);
    mat_multv(m, n, A, x, r);
    double soma = 0.0;
    for (int i = 0; i < m; ++i) {
        r[i] = b[i] - r[i];
        soma += r[i] * r[i];
    }
    double norma = sqrt(soma);
    vet_libera(r);

    return norma;
}

// Ajuste de y = a + b x + c x^2

double ajuste_parabola(int n, double* px, double* py, double* a, double* b, double* c) {
    double** A = mat_cria(n, 3);
    for (int i = 0; i < n; ++i) {
        A[i][0] = 1.0;
        A[i][1] = px[i];
        A[i][2] = px[i] * px[i];
    }
    double* sol = vet_cria(3);
    double erro = mmq(n, 3, A, py, sol);
    *a = sol[0];
    *b = sol[1];
    *c = sol[2];
    mat_libera(n, A);
    vet_libera(sol);
    return erro;
}

// Ajuste de y = a + b x + c x^2 + d x^3

double ajuste_cubica(int n, double* px, double* py, double* a, double* b, double* c, double* d) {
    double** A = mat_cria(n, 4);
    for (int i = 0; i < n; ++i) {
        A[i][0] = 1.0;
        A[i][1] = px[i];
        A[i][2] = px[i] * px[i];
        A[i][3] = px[i] * px[i] * px[i];
    }
    double* sol = vet_cria(4);
    double erro = mmq(n, 4, A, py, sol);
    *a = sol[0];
    *b = sol[1];
    *c = sol[2];
    *d = sol[3];
    mat_libera(n, A);
    vet_libera(sol);
    return erro;
}

// Ajuste exponencial y = a * exp(b x)

double ajuste_exponencial_exp(int n, double* px, double* py, double* a, double* b) {
    double* Y = vet_cria(n);
    for (int i = 0; i < n; ++i) {
        Y[i] = (py[i] > 0) ? log(py[i]) : 0.0;
    }
    double** A = mat_cria(n, 2);
    for (int i = 0; i < n; ++i) {
        A[i][0] = 1.0;
        A[i][1] = px[i];
    }
    double* sol = vet_cria(2);
    double erro = mmq(n, 2, A, Y, sol);
    *a = exp(sol[0]);
    *b = sol[1];
    vet_libera(Y);
    vet_libera(sol);
    mat_libera(n, A);
    return erro;
}