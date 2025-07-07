#include <stdio.h>
#include <math.h>
#include "massamola.h"

typedef struct { double h, v; } Vec2;

// Parametros
#define k 0.3                           // rigidez da mola
#define r 200                           // comprimento de repouso da mola
#define m 2.0                           // massa do corpo
static const Vec2 G = { 0.0, 9.8 };     // aceleração da gravidade
static const Vec2 W = { 10.0, 0.0 };    // força inicial de vento
#define d 0.002                         // coeficiente de amortecimento

// Funcoes
#define fg(m, g) (m * g)
#define fw(w, t) (w * exp(-t / 20))
#define fkx(k, r, x, y) (-k * (sqrt(x * x + y * y) - r) * (x / sqrt(x * x + y * y)))
#define fky(k, r, x, y) (-k * (sqrt(x * x + y * y) - r) * (y / sqrt(x * x + y * y)))

void forca (double t, double x, double y, double* fx, double* fy){
    *fx = fkx(k, r, x, y) + fw(W.h, t);
    *fy = fky(k, r, x, y) + fg(m, G.v);
}

double evolui (double t, double h, double x, double y, double xp, double yp, double* xn, double* yn){
    double fx, fy;
    forca(t, x, y, &fx, &fy);

    *xn = x + (1 - d) * (x - xp) + pow(h, 2) * (fx / m);
    *yn = y + (1 - d) * (y - yp) + pow(h, 2) * (fy / m);

    return t + h;
}

void simula (double x0, double y0, double t, int n, double* x, double* y){
    double h0 = t / n;
    double ti = 0;
    double xp, yp, xa, ya, xn, yn;

    // Primeiro passo
    xp = x0;
    yp = y0;
    xa = x0;
    ya = y0;
    ti = evolui(ti, h0, xa, ya, xp, yp, &xn, &yn);
    x[0] = xn;
    y[0] = yn;
    
    // Resto...
    for (int i = 1; i < n; i++)
    {
        xp = xa;
        yp = ya;
        xa = xn;
        ya = yn;
        ti = evolui(ti, h0, xa, ya, xp, yp, &xn, &yn);
        x[i] = xn;
        y[i] = yn;
    }
    
}