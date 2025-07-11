#ifndef PENDULUM_H
#define PENDULUM_H

#include <stddef.h>   /* size_t */
#include <stdio.h>    /* FILE *  */

/* ---------- Estruturas  ---------- */
typedef struct {
    double theta;   /* rad */
    double omega;   /* rad/s */
} State;

typedef struct {
    double g;       /* 9.81 m/s² */
    double l;       /* comprimento do fio (m) */
} Params;

/* ---------- Assinaturas ---------- */
/* Derivada f(t,y) -> dy/dt  */
void pendulum_deriv(double t, const State *y, State *dy, const Params *p);

/* Integra um ciclo completo (até 'crossings' inversões)    */
/*  - Salva amostras em 'out', até máximo 'capacity'.        */
/*  - Retorna #amostras efetivas (≤capacity).                */
size_t pendulum_simulate(State y0,
                         double h,
                         unsigned crossings,
                         State *out,
                         size_t capacity,
                         const Params *p);

/* Grava CSV (t,θ,ω) para inspeção offline */
int pendulum_write_csv(const char *filepath,
                       const State *series,
                       const double *times,
                       size_t n);

#endif /* PENDULUM_H */
