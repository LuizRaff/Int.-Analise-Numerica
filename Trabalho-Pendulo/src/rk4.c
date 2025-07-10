#include <stdio.h>
#include <math.h>

double RungeKutta(double t0, double t1, double h, double y0, double (*f)(double t, double y))
{
    double k0, k1, k2, k3;
    double yi = y0;

    while (t0 < t1)
    {
        k0 = h * f(t0, yi);
        k1 = h * f((t0 + h / 2), (yi) + (k0 / 2));
        k2 = h * f((t0 + h / 2), (yi) + (k1 / 2));
        k3 = h * f(t0 + h, yi + k2);
        yi = yi + ((1.0 / 6.0) * (k0 + (2 * k1) + (2 * k2) + k3));

        t0 = t0 + h;
    }

    return yi;
}

double RungeKuttaStep(double t0, double t1, double h, double y0, double (*f)(double t, double y))
{
    double k0, k1, k2, k3;
    double yi = y0;

    k0 = h * f(t0, yi);
    k1 = h * f((t0 + h / 2), (yi) + (k0 / 2));
    k2 = h * f((t0 + h / 2), (yi) + (k1 / 2));
    k3 = h * f(t0 + h, yi + k2);
    return yi + ((1.0 / 6.0) * (k0 + (2 * k1) + (2 * k2) + k3));
}

double RungeKuttaAdapt(double t0, double t1, double y0, double (*f)(double t, double y), double tol)
{
    double hi = pow(10, -7);
    double y_1passo, y_2passo1, y_2passo2, delta, fator;

    while (t0 < t1)
    {
        if (t0 + hi > t1)
        {
            hi = t1 - t0;
        }

        y_1passo = RungeKuttaStep(t0, t0 + hi, hi, y0, f);

        y_2passo1 = RungeKuttaStep(t0, t0 + (hi / 2), hi / 2, y0, f);
        y_2passo2 = RungeKuttaStep(t0 + (hi / 2), t0 + hi, hi / 2, y_2passo1, f);

        delta = (y_2passo2 - y_1passo) / 15.0;

        fator = pow(tol / fabs(delta), 1.0 / 5.0);

        if (fator >= 1.0)
        {
            t0 = t0 + hi;
            y0 = y_2passo2 + delta;
            hi = fmin(1.2, fator) * hi;
        }
        else
        {
            hi = 0.8 * fator * hi;
        }
    }

    return y0;
}
