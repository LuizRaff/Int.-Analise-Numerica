#include "taylor.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define PI 3.141592653589793

int main (void)
{
  // escreva seu teste aqui
  double x1 = 0.2617993878;
  double y1 = avalia_seno(10, x1);
  printf("Teste: x: %.10f (PI/12.0)\t", x1);
  printf("Resultado: %.10f\n", y1);

  double x2 = 0.3490658504;
  double y2 = avalia_seno(10, x2);
  printf("Teste: x: %.10f (PI/9.0)\t", x2);
  printf("Resultado: %.10f\n", y2);

  double x3 = 0.4487989505;
  double y3 = avalia_seno(10, x3);
  printf("Teste: x: %.10f (PI/7.0)\t", x3);
  printf("Resultado: %.10f\n", y3);

  double x4 = 0.7853981634;
  double y4 = avalia_seno(10, x4);
  printf("Teste: x: %.10f (PI/4.0)\t", x4);
  printf("Resultado: %.10f\n", y4);

  double x5 = 1.0471975512;
  double y5 = avalia_seno(10, x5);
  printf("Teste: x: %.10f (PI/3.0)\t", x5);
  printf("Resultado: %.10f\n", y5);

  return 0;
}
