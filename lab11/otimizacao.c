/* otimizacao.c */
#include <math.h>
#include "otimizacao.h"

int msa(double a, double b, double (*f)(double), double tol, double *xmin) {
    const double g = (sqrt(5.0) - 1.0) / 2.0;
    double x1 = a + (1.0 - g) * (b - a);
    double x2 = a + g * (b - a);
    double f1 = f(x1), f2 = f(x2);
    int it;

    for (it = 0; it <= 50; ++it) {
        if (fabs(b - a) / 2.0 <= tol) {
            break;
        }

        if (f1 <= f2) {
            b  = x2;
            x2 = x1;      
            f2 = f1;
            x1 = a + (1.0 - g) * (b - a);
            f1 = f(x1);
        } else {
            a  = x1;
            x1 = x2;      
            f1 = f2;
            x2 = a + g * (b - a);
            f2 = f(x2);
        }
    }

    *xmin = 0.5 * (a + b);
    return it;
}

int mips(double r, double delta, double (*f)(double), double tol, double *xmin) {
    double r0 = r, s = r - delta, t = r + delta;
    double fr = f(r0), fs = f(s), ft = f(t);
    int it;

    double denom = 0.0, x = 0.0;
    for (it = 1; it <= 50; ++it) {
        denom = (s - r0) * (ft - fs) - (fs - fr) * (t - s);

        if (fabs(denom) < 1e-10) {
            x = (r0 + s + t) / 3.0;
        } else {
            x = 0.5 * (r0 + s) - (fs - fr) * (t - r0) * (t - s) / (2.0 * denom);
        }

        double fx = f(x);

        r0 = s;  
        fr = fs;
        s  = t;  
        fs = ft;
        t  = x;  
        ft = fx;

        if (it >= 3 && fabs(fs - ft) <= tol)
            break;
    }

    if (it > 50) return 0;
    *xmin = 0.5 * (s + t);
    return it;
}
