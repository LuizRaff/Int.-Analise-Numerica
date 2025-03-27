#include "raiz.h"
#include <math.h>
#include <stdio.h>

#define PI 3.1415926535897932384626433832795

// exemplo para contagem de avaliacoes da funcao
// defina N=0 antes de chamar o metodo da bissecao
int N;
static double funcaoQ2 (double x)
{
  N++;
  return (x*x*x) + (2*(x*x)) - 2;
}

static double funcaoQ3 (double x)
{
  N++;
  return (x*x*x*x) + x + 1;
}

static double funcaoQ4 (double m)
{
  N++;
  double g = 9.8;
  double c = 15.0;
  double v = 35.0;
  double t = 9.0;

  return ( ( (g * m) / c) * (1 - exp( (-c / m) * t) ) ) - v;
}

int main (void)
{
  printf("it: iteracoes da bissecao, av: avaliacoes da funcao\n");
  double r;
  int av;
  int it;

  N = 0;
  it = bissecao(-3, 3, funcaoQ2, &r);
  av = N;
  if (it == -1) printf(">>> Q1 de -3 a +3: funcao nao convergiu it:%d av:%d\n", it, av);
  else printf(">>> Q1 de -3 a +3: c:%.9f it:%d av:%d\n", r, it, av);

  N = 0;
  it = bissecao(-3, 3, funcaoQ3, &r);
  av = N;
  if (it == -1) printf(">>> Q2 de -3 a +3: funcao nao convergiu it:%d av:%d\n", it, av);
  else printf(">>> Q2 de -3 a +3: c:%.9f it:%d av:%d\n", r, it, av);

  N = 0;
  it = bissecao(-5, 5, funcaoQ2, &r);
  av = N;
  if (it == -1) printf(">>> Q1 de -5 a +5: funcao nao convergiu it:%d av:%d\n", it, av);
  else printf(">>> Q1 de -5 a +5: c:%.9f it:%d av:%d\n", r, it, av);

  N = 0;
  it = bissecao(0, 150, funcaoQ4, &r);
  av = N;
  if (it == -1) printf(">>> Q3 de 0 a 150: funcao nao convergiu it:%d av:%d\n", it, av);
  else printf(">>> Q3 de 0 a 150: c:%.9f it:%d av:%d\n", r, it, av);

  N = 0;
  it = bissecao(0, 250, funcaoQ4, &r);
  av = N;
  if (it == -1) printf(">>> Q3 de 0 a 250: funcao nao convergiu it:%d av:%d\n", it, av);
  else printf(">>> Q3 de 0 a 250: c:%.9f it:%d av:%d\n", r, it, av);

  N = 0;
  it = bissecao(0, 50, funcaoQ4, &r);
  av = N;
  if (it == -1) printf(">>> Q3 de 0 a  50: funcao nao convergiu it:%d av:%d\n", it, av);
  else printf(">>> Q3 de 0 a  50: c:%.9f it:%d av:%d\n", r, it, av);

  return 0;
}

