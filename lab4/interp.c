#include <stdio.h>
#include <math.h>
#include "interp.h"

void regular (int n, double a, double b, double* xi){
    double distancia = (b-a)/(n-1);

    for (int i = 0; i < n - 1; i++)
    {
        xi[i] = a + i * distancia;
    }

    xi[n-1] = b;    
    return;
}

#define PI 3.141592653589793
void chebyshev (int n, double a, double b, double* xi){
    for (int i = 0, j = 1; i < n; i++, j+=2)
    {
        xi[i] = ((b - a) / 2) * cos((j * PI) / (2 * n)) + ((a + b) / 2);
    }

    return;
}

double F (double (*f) (double), double* xk, int i, int j){
    if (i == j){
        return f(xk[i]);
    } else {
        return ( F (f, xk, i+1, j) - F (f, xk, i, j-1) ) / (xk[j] - xk[i]);
    }
}

void coeficientes (int n, double* xi, double (*f) (double), double* bi){
    for (int i = 0; i < n; i++)
    {
        bi[i] = F(f, xi, 0, i);
    }
    
    return;
}

double lk (int n, double* xi, double x){
    double lkx = 1;
    for (int j = 0; j < n; j++)
    {
        lkx *= (x - xi[j]);
    }
    return lkx;
}

double avalia (int n, double* xi, double* bi, double x){
    double px = 0;
    for (int i = 0; i < n; i++)
    {
        px += lk(i, xi, x) * bi[i];
    }
    return px;
}