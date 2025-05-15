#include "ode.h"
#include <stdio.h>
#include <math.h>

static int N;
static double f(double t, double x)
{
  N++;
  return t * x + t * t * t;
}

#define S 10.0542731796122

int main(void)
{
  N = 0;
  double e = 0.0; // TODO: chamar RungeKutta
  e = RungeKutta(0.0, 2.4, 0.001, -1, f);
  printf("RungeKutta: N=%d rk=%g diff=%g\n", N, e, fabs(S - e));
  N = 0;
  double g = 0.0; // TODO: chamar RungeKuttaAdapt
  g = RungeKuttaAdapt(0.0, 2.4, -1, f, pow(10, -12));
  printf("RungeKuttaAdapt: N=%d rk=%g diff=%g\n", N, g, fabs(S - g));
  return 0;
}
