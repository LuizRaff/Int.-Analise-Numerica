#include "massamola.h"
#include <stdio.h>

void testaforca (double t, double x, double y) 
{
  double fx, fy;
  // TODO: chamar funcao 'forca'
  forca(t, x, y, &fx, &fy);
  // TODO: imprimir forca fx e fy
  printf("[fx,fy]: %.6f %.6f\n", fx, fy);
}

void testaevolui (double t, double h, double x1, double y1, double x0, double y0) 
{
  double x2, y2;
  double th = evolui(t, h, x0, y0, x1, y1, &x2, &y2);  // TODO: chamar funcao 'evolui'
  // TODO: imprimir resultado de evolui
  printf("[x, y]: %.6f %.6f (%.6f)\n", x2, y2, th);
}

int main (void)
{
  testaforca(0.0, 300.0, 0.0);
  testaforca(1.0, 200.0, 0.0);
  testaforca(2.0, 100.0, 0.0);
  testaforca(3.0, 300.0, 100.0);
  testaforca(4.0, 200.0, 100.0);
  testaforca(5.0, 100.0, 100.0);

  testaevolui(0.0, 0.2, 300.0, 0.0, 300.0, 0.0);
  testaevolui(1.0, 0.2, 200.0, 0.0, 200.0, 0.0);
  testaevolui(2.0, 0.2, 100.0, 0.0, 100.0, 0.0);
  testaevolui(3.0, 0.2, 300.0, 100.0, 300.0, 100.0);
  testaevolui(4.0, 0.2, 200.0, 100.0, 200.0, 100.0);
  testaevolui(5.0, 0.2, 100.0, 100.0, 100.0, 100.0);

  // Completar teste da funcao simula
  double r = 200;
  double x[1000],y[1000];
  // TODO: chama simula
  simula(200.0, 0.0, 100.0, 1000, x, y);
  // TODO: imprimir cada x e y
  for (int i = 0; i < 1000; i++)
  {
    printf("(%.6f, %.6f),\n", x[i], y[i]);
  }
   
  return 0;
}
