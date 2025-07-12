#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stddef.h>
#include "../headers/pendulum.h"
#include "../headers/rk4.h"

double detect_period_n(const double *times,
                       const double *omega,
                       size_t n,
                       unsigned inv_count)
{
    if (!times || !omega || n < 2 || inv_count == 0)
        return -1.0;

    unsigned found = 0;
    double v_prev = omega[0];
    // double t_prev = times[0];
    double t_nth   = 0.0;

    for (size_t i = 1; i < n; ++i) {
        double v_cur = omega[i];
        if (v_prev * v_cur <= 0.0) {
            // we hit the k-th inversion somewhere between i-1 and i
            double t1 = times[i-1];
            double t2 = times[i];
            double frac = fabs(v_prev) / (fabs(v_prev) + fabs(v_cur));
            double t_zero = t1 + frac * (t2 - t1);

            found++;
            if (found == inv_count) {
                t_nth = t_zero;
                break;
            }
        }
        v_prev = v_cur;
    }
    if (found < inv_count) return -1.0;

    // inv_count inversions = inv_count × (½ period)  ⇒  period = (2 * t_nth) / inv_count
    return (2.0 * t_nth) / (double)inv_count;
}

// Analytic small-angle solver and period
static double analytic_theta(double theta0, double t, const Params *p) {
    return theta0 * cos(sqrt(p->g / p->l) * t);
}
static double analytic_period(const Params *p) {
    return 2.0 * M_PI * sqrt(p->l / p->g);
}

// High-resolution timer (seconds)
static double now_sec(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec * 1e-9;
}

int main(void) {
    const Params p = { .g = 9.81, .l = 1.0 };

    FILE *f = fopen("data/metrics.csv", "w");
    if (!f) { perror("fopen"); return 1; }
    fprintf(f, "mode,theta0,period,steps,cpu_time,avg_dt,max_error,real_time\n");

    for (size_t i = 1; i < 9000; ++i) {
        double th0_deg = (double) i / 100;
        double th0 = th0_deg * M_PI / 180.0;
        double T_lin = analytic_period(&p);

        // Analytic baseline
        fprintf(f, "analytic,%.2f,%.8f,0,0,0.0,0.0,yes\n", th0_deg, T_lin);

        // Fixed-step RK4
        double hs[] = {1e-2, 1e-3, 1e-4};
        for (int j = 0; j < 3; ++j) {
            double h = hs[j];
            size_t cap = 200000;
            State *series = malloc(cap * sizeof(State));
            double *times = malloc(cap * sizeof(double));
            double *omegas = malloc(cap * sizeof(double));

            double t_start = now_sec();
            size_t n = rk4_integrate_fixed(
                (State){ .theta = th0, .omega = 0.0 },
                0.0,
                10.0 * T_lin,
                h,
                series,
                cap,
                (void(*)(double,const State*,State*,const void*))pendulum_deriv,
                &p
            );
            double t_stop = now_sec();

            // Compute times, omegas, max error
            double max_err = 0.0;
            for (size_t k = 0; k < n; ++k) {
                times[k] = k * h;
                omegas[k] = series[k].omega;
                double err = fabs(series[k].theta - analytic_theta(th0, times[k], &p));
                if (err > max_err) max_err = err;
            }
            double avg_dt = h;  // fixed step

            // Period detection using 10th inversion
            double T_num = detect_period_n(times, omegas, n, 10);
            double cpu = t_stop - t_start;
            double avg_step = cpu / (double)n;
            const char *rt = (avg_step < avg_dt) ? "yes" : "no";

            fprintf(f,
                "fixed_%.0e,%.2f,%.8f,%zu,%.6f,%.6f,%.6f,%s\n",
                h, th0_deg, T_num, n, cpu, avg_dt, max_err, rt
            );

            free(series);
            free(times);
            free(omegas);
        }

        // Adaptive RK4
        {
            double h0 = 1e-3, eps = 1e-5;
            size_t cap = 200000;
            State *series = malloc(cap * sizeof(State));
            double *times = malloc(cap * sizeof(double));
            double *omegas = malloc(cap * sizeof(double));

            double t_start = now_sec();
            size_t n = rk4_integrate_adaptive(
                (State){ .theta = th0, .omega = 0.0 },
                0.0,
                10.0 * T_lin,
                h0,
                eps,
                series,
                times,
                cap,
                (void(*)(double,const State*,State*,const void*))pendulum_deriv,
                &p
            );
            double t_stop = now_sec();

            // Compute omegas, max error and avg_dt from actual time steps
            double max_err = 0.0;
            double sum_dt = 0.0;
            for (size_t k = 0; k < n; ++k) {
                omegas[k] = series[k].omega;
                double err = fabs(series[k].theta - analytic_theta(th0, times[k], &p));
                if (err > max_err) max_err = err;
                if (k > 0) sum_dt += (times[k] - times[k-1]);
            }
            double avg_dt = sum_dt / (double)(n - 1);

            double T_num = detect_period_n(times, omegas, n, 10);
            double cpu = t_stop - t_start;
            double avg_step = cpu / (double)n;
            const char *rt = (avg_step < avg_dt) ? "yes" : "no";

            fprintf(f,
                "adaptive,%.2f,%.8f,%zu,%.6f,%.6f,%.6f,%s\n",
                th0_deg, T_num, n, cpu, avg_dt, max_err, rt
            );

            free(series);
            free(times);
            free(omegas);
        }
    }

    fclose(f);
    printf("Metrics collection complete: data/metrics.csv generated.\n");
    return 0;
}
