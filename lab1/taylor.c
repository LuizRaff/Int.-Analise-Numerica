#include "taylor.h"
#include <stdlib.h>

double avalia_taylor (int n, double *c, double x0, double x){
    if (n == 0){
        return 0;
    }

    double fac = 1.0;
    double delta = 1.0;
    double fx = c[0];
    for (int i = 1; i < n; i++)
    {
        delta *= (x - x0);
        fac *= i;

        fx += c[i] * (delta / fac);
    }
    
    return fx;
}

double avalia_seno (int n, double x){
    double cPossibilidades[4] = {0.0, 1.0, 0.0, -1.0};
    double* coeficientes = (double*)malloc(n * sizeof(double));

    for (int i = 0; i < n; i++)
    {
        coeficientes[i] = cPossibilidades[i%4];
    }

    double resultado = avalia_taylor(n, coeficientes, 0.0, x);

    free(coeficientes);

    return resultado;
}