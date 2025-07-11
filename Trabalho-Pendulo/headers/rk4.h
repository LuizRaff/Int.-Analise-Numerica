#ifndef RK4_H
#define RK4_H

#include "pendulum.h"

/* Passo único RK4 passo FIXO */
void rk4_step(double t,
              const State *y,
              double h,
              State *yout,
              void (*f)(double,const State*,State*,const void*),
              const void *fparams);

/* Integra até t_end usando passo FIXO, armazenando em series[] */
size_t rk4_integrate_fixed(State y0,
                           double t0,
                           double t_end,
                           double h,
                           State *series,
                           size_t capacity,
                           void (*f)(double,const State*,State*,const void*),
                           const void *fparams);

/* Versão ADAPTATIVA (erro local ≤ eps) – step-doubling */
size_t rk4_integrate_adaptive(State y0,
                              double t0,
                              double t_end,
                              double h_init,
                              double eps,
                              State *series,
                              double *times,
                              size_t capacity,
                              void (*f)(double,const State*,State*,const void*),
                              const void *fparams);

#endif /* RK4_H */
