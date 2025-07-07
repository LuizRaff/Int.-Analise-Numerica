#ifndef GAUSS_SEIDEL_H
#define GAUSS_SEIDEL_H

int gaussseidel (int n, double** A, double* b, double* x, double tol);
int sor_gaussseidel (int n, double** A, double* b, double* x, double tol, double w);

#endif