#include "sistlinear.h"
#include "matriz.h"
#include "vetor.h"
#include <stdio.h>
#include <math.h>

void gauss (int n, double** a, double* b, double* x){
    double f;
    unsigned int p;

    for (unsigned int i = 0; i < n - 1; i++)
    {
        // Pivotamento
        p = i;
        for (unsigned int k = i + 1; k < n; k++)
        {
            if (fabs(a[k][i]) > fabs(a[p][i]))
            {
                p = k;
            }
        }

        for (unsigned int k = i; k < n; k++)
        {
            double temp = a[i][k];
            a[i][k] = a[p][k];
            a[p][k] = temp;
        }
        
        double temp = b[i];
        b[i] = b[p];
        b[p] = temp;
        
        // Eliminacao
        for (unsigned int j = i + 1; j < n; j++)
        {
            f = a[j][i] / a[i][i];
            for (unsigned int k = i; k < n; k++)
            {
                a[j][k] = a[j][k] - (f * a[i][k]);
            }
            b[j] = b[j] - (f * b[i]);
        }
        
    }
    
    // Retrosubstituicao
    double s;
    for (int i = n - 1; i >= 0; i--)
    {
        s = 0;
        for (int j = i + 1; j < n; j++)
        {
            s = s + a[i][j] * x[j];
        }

        x[i] = (b[i] - s) / a[i][i];
    }
    
}