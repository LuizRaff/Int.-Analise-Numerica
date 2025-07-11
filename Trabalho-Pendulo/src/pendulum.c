#include <math.h>
#include "../headers/pendulum.h"
#include "../headers/rk4.h"

/*  gobal auxiliar: converte graus→rad apenas aqui  */
#define DEG2RAD(x) ((x)*M_PI/180.0)

/* ---------- Derivada ---------- */
void pendulum_deriv(double t, const State *y, State *dy, const Params *p)
{
    (void)t;        /* t não entra: sistema autônomo */
    dy->theta = y->omega;
    dy->omega = -(p->g / p->l) * sin(y->theta);
}

/* ---------- Simulação de um número fixo de inversões ---------- */
size_t pendulum_simulate(State y0, double h, unsigned crossings,
                         State *out, size_t cap, const Params *p)
{
    double t = 0.0;
    unsigned cross = 0;
    size_t n = 0;
    State y = y0;
    double last_omega = y.omega;

    while (cross < crossings && n < cap) {
        out[n++] = y;

        State ynxt;
        rk4_step(t, &y, h, &ynxt,
                 (void(*)(double,const State*,State*,const void*))pendulum_deriv, p);

        /* detecta inversão de velocidade */
        if ((y.omega > 0 && ynxt.omega < 0) || (y.omega < 0 && ynxt.omega > 0)) {
            cross++;
        }
        last_omega = y.omega;
        y = ynxt;
        t += h;
    }
    return n;
}

/* ---------- CSV ---------- */
int pendulum_write_csv(const char *path,
                       const State *series, const double *t, size_t n)
{
    FILE *fp = fopen(path,"w");
    if (!fp) return -1;
    fprintf(fp,"t,theta,omega\n");
    for (size_t i=0;i<n;i++)
        fprintf(fp,"%.10f,%.10f,%.10f\n",t[i],series[i].theta,series[i].omega);
    fclose(fp);
    return 0;
}
