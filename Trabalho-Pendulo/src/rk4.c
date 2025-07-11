#include <math.h>
#include "../headers/rk4.h"

/* Passo único ------------------------------------------------------------*/
void rk4_step(double t, const State *y, double h, State *yout,
              void (*f)(double,const State*,State*,const void*),
              const void *p)
{
    State k1,k2,k3,k4,tmp;

    f(t,           y,          &k1, p);

    tmp.theta = y->theta + 0.5*h*k1.theta;
    tmp.omega = y->omega + 0.5*h*k1.omega;
    f(t+0.5*h,   &tmp,        &k2, p);

    tmp.theta = y->theta + 0.5*h*k2.theta;
    tmp.omega = y->omega + 0.5*h*k2.omega;
    f(t+0.5*h,   &tmp,        &k3, p);

    tmp.theta = y->theta + h*k3.theta;
    tmp.omega = y->omega + h*k3.omega;
    f(t+h,       &tmp,        &k4, p);

    yout->theta = y->theta + (h/6.0)*(k1.theta + 2*k2.theta + 2*k3.theta + k4.theta);
    yout->omega = y->omega + (h/6.0)*(k1.omega + 2*k2.omega + 2*k3.omega + k4.omega);
}

/* Integração passo fixo --------------------------------------------------*/
size_t rk4_integrate_fixed(State y0, double t0, double t_end, double h,
                           State *series, size_t cap,
                           void (*f)(double,const State*,State*,const void*),
                           const void *p)
{
    size_t n = 0;
    double t = t0;
    State y = y0;
    while (t < t_end && n < cap) {
        series[n++] = y;
        State ynext;
        rk4_step(t, &y, h, &ynext, f, p);
        y = ynext;
        t += h;
    }
    return n;
}

/* Integração adaptativa (simplificada) -----------------------------------*/
static double state_err(const State *a, const State *b)
{
    return fmax(fabs(a->theta - b->theta),
                fabs(a->omega - b->omega));
}

size_t rk4_integrate_adaptive(State y0, double t0, double t_end,
                              double h, double eps,
                              State *series, double *times, size_t cap,
                              void (*f)(double,const State*,State*,const void*),
                              const void *p)
{
    size_t n = 0;
    double t = t0;
    State y = y0;

    while (t < t_end && n < cap) {
        series[n] = y;
        times[n]  = t;
        n++;

        /* --- estimativa por step-doubling ---*/
        State y_full;
        rk4_step(t, &y, h, &y_full, f, p);

        State y_half;
        rk4_step(t, &y, 0.5*h, &y_half, f, p);
        State y_half2;
        rk4_step(t+0.5*h, &y_half, 0.5*h, &y_half2, f, p);

        double err = state_err(&y_full, &y_half2);
        double fac = pow(eps/err, 0.25)*0.9;
        if (fac < 0.2) fac = 0.2;
        if (fac > 5.0) fac = 5.0;

        if (err <= eps) {          /* aceita passo */
            y = y_half2;
            t += h;
        }
        h *= fac;
        if (h < 1e-6) h = 1e-6;    /* evita passo ridículo */
    }
    return n;
}
