#include "raiz.h"
#include <math.h>

int bissecao (double a, double b, double (*f) (double x), double* r){
    double A = a;
    double B = b;
    
    *r = (A + B) / 2;
    double Err = (B - A) / 2;
    int iFunc = 0;
    double yA = f(a);
    double yC;

    if (yA * f(b) > 0) return -1;

    while(Err >= (pow(10, -8)*0.5)){
        yC = f(*r);

        if (fabs(yC) < (pow(10, -12))){
            return iFunc;
        }
        else if((yA * yC) < 0){
            B = *r;
        }
        else{
            A = *r;
            yA = yC;
        }

        Err = (B - A) / 2;
        *r = (A + B) / 2;

        iFunc++;
    }

    return iFunc;
}