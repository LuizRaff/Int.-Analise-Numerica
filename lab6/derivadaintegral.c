#include "derivadaintegral.h"
#include <math.h>

double derivada(double (*f)(double x), double x, double h) {
    return (f(x + h) - f(x - h)) / (2.0 * h);
}

double simpson(double (*f)(double), double a, double b, int n) {
    double h = (b - a) / n;
    double sum = f(a) + f(b);
    for (int i = 1; i < n; ++i) {
        double xi = a + i * h;
        sum += (i % 2 == 0) ? 2.0 * f(xi) : 4.0 * f(xi);
    }
    return sum * h / 3.0;
}

static double adaptive_simpson_rec(double (*f)(double), double a, double b,
                                   double eps, double S, double fa, double fb, double fc) {
    double c = 0.5 * (a + b);
    double h = 0.5 * (b - a);
    double d = 0.5 * (a + c);
    double e = 0.5 * (c + b);
    double fd = f(d), fe = f(e);
    double Sleft  = (h / 6.0) * (fa + 4.0 * fd + fc);
    double Sright = (h / 6.0) * (fc + 4.0 * fe + fb);
    double delta = Sleft + Sright - S;
    if (fabs(delta) <= 15.0 * eps) {
        return Sleft + Sright + delta / 15.0;
    }
    return adaptive_simpson_rec(f, a,   c, eps/2.0, Sleft,  fa, fc, fd)
         + adaptive_simpson_rec(f, c,   b, eps/2.0, Sright, fc, fb, fe);
}

double simpsonadaptativo(double (*f)(double), double a, double b, double tol) {
    double c  = 0.5 * (a + b);
    double fa = f(a), fb = f(b), fc = f(c);
    double S  = (b - a) / 6.0 * (fa + 4.0 * fc + fb);
    return adaptive_simpson_rec(f, a, b, tol, S, fa, fb, fc);
}
