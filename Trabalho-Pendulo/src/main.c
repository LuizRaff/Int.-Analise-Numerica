#include <stdio.h>
#include "../headers/pendulum.h"
#include "../headers/rk4.h"
#include <stdlib.h>
#include <math.h>

int generate_sample_csv(void)
{
    const Params p = {.g = 9.81, .l = 1.0};
    State y0 = {.theta = 0.1 /*rad*/, .omega = 0.0};

    const size_t CAP = 20000;
    State *series = malloc(CAP * sizeof(State));
    double *times = malloc(CAP * sizeof(double));

    size_t n = rk4_integrate_fixed(y0, 0.0, 10.0, 0.001,
                                   series, CAP,
         (void(*)(double,const State*,State*,const void*))pendulum_deriv, &p);
    pendulum_write_csv("data/θ_vs_t.csv", series, times, n);

    free(series); free(times);
    return 0;
}

int pendulum_write_csv_xy(const char *path,
                          const State *series,
                          const double *times,
                          size_t n,
                          const Params *p)
{
    FILE *fp = fopen(path,"w");
    if (!fp) return -1;
    fprintf(fp,"t,theta,omega,x,y\n");
    for (size_t i = 0; i < n; i++) {
        double th = series[i].theta;
        double x  = p->l * sin(th);
        double y  = -p->l * cos(th);
        fprintf(fp,"%.10f,%.10f,%.10f,%.10f,%.10f\n",
                times[i], th, series[i].omega, x, y);
    }
    fclose(fp);
    return 0;
}


int main(void)
{
    const Params p = {.g = 9.81, .l = 1.0};
    State y0 = {.theta = 0.2, .omega = 0.0};

    // Pre-allocate buffers
    size_t   cap    = 100000;    // adjust as needed
    State   *series = malloc(cap * sizeof(State));
    double  *times  = malloc(cap * sizeof(double));

    // Run adaptive RK4: eps = 1e-5, initial h = 1e-3
    size_t n = rk4_integrate_adaptive(
        y0,            // initial state
        0.0,           // t0
        10.0,          // t_end (e.g. 10 s)
        1e-3,          // h_init
        1e-5,          // eps (local error tol)
        series,        // output states
        times,         // output times
        cap,           // capacity
        (void(*)(double,const State*,State*,const void*))pendulum_deriv,
        &p
    );

    if (n == 0) {
        fprintf(stderr, "Adaptive integrator failed or capacity too small\n");
        return 1;
    }

    // Write CSV with (t,θ,ω,x,y)
    if (pendulum_write_csv_xy("data/θωxy_adaptive.csv",
                                       series, times, n, &p) != 0) {
        fprintf(stderr, "Failed to write CSV\n");
        return 1;
    }

    printf("Adaptive run complete: %zu samples → data/θωxy_adaptive.csv\n", n);

    free(series);
    free(times);

    size_t N = 10000;
    series = malloc(N * sizeof(State));
    times  = malloc(N * sizeof(double));

    n = rk4_integrate_fixed(
        y0, 0.0, 10.0, 0.001,
        series, N,
        (void(*)(double,const State*,State*,const void*))pendulum_deriv,
        &p
    );

    if(pendulum_write_csv_xy("data/θωxy_fixed.csv", series, times, n, &p) != 0){
        fprintf(stderr, "Failed to write fixed CSV\n");
        return 1;
    }
    free(series); free(times);
    return 0;
}
