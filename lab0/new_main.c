#include "vetor.h"
#include "matriz.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void) {
    /* ============================================================
       Teste 1: Criação e impressão de vetores
       - Cria um vetor dinâmico e um vetor estático
    ============================================================ */
    printf("Teste 1: Vetores\n");
    double *v = vet_cria(2);
    v[0] = 1.0;
    v[1] = 2.0;
    double w_static[] = {1.0, 2.0};
    
    printf("Vetor dinâmico v:\n");
    vet_imprime(2, v);
    printf("Vetor estático w_static:\n");
    vet_imprime(2, w_static);
    
    vet_libera(v);

    /* ============================================================
       Teste 2: Criação e impressão de matrizes
       - Cria uma matriz dinâmica e imprime uma matriz estática (ponteiro para ponteiro)
    ============================================================ */
    printf("\nTeste 2: Matrizes\n");
    double **A = mat_cria(3, 2);
    A[0][0] = 1.0; A[0][1] = 2.0;
    A[1][0] = 3.0; A[1][1] = 4.0;
    A[2][0] = 5.0; A[2][1] = 6.0;
    
    printf("Matriz dinâmica A:\n");
    mat_imprime(3, 2, A);
    
    // Matriz estática em formato ponteiro para ponteiro
    double linha1[] = {1.0, 2.0};
    double linha2[] = {3.0, 4.0};
    double linha3[] = {5.0, 6.0};
    double *B[] = {linha1, linha2, linha3};
    
    printf("Matriz estática B:\n");
    mat_imprime(3, 2, B);
    
    mat_libera(3, A);

    /* ============================================================
       Teste 3: Transposição de matriz
       - Dada uma matriz 3x2, calcula sua transposta (2x3)
    ============================================================ */
    printf("\nTeste 3: Transposição de matriz\n");
    int m = 3, n = 2;
    double **mat = mat_cria(m, n);
    mat[0][0] = 1.0; mat[0][1] = 2.0;
    mat[1][0] = 3.0; mat[1][1] = 4.0;
    mat[2][0] = 5.0; mat[2][1] = 6.0;
    
    double **T = mat_cria(n, m); // Transposta terá dimensão 2x3
    mat_transposta(m, n, mat, T);
    
    printf("Matriz original (mat):\n");
    mat_imprime(m, n, mat);
    printf("Transposta (T):\n");
    mat_imprime(n, m, T);
    
    mat_libera(m, mat);
    mat_libera(n, T);

    /* ============================================================
       Teste 4: Multiplicação de matriz por vetor (mat_multv)
       - Supondo a multiplicação padrão:
         Dada uma matriz A (m x n) e um vetor v (dimensão n), 
         o resultado w terá dimensão m.
         Exemplo: 
         A = [ [1,2,3],
               [4,5,6] ]
         v = [1,1,1]  => w = [6,15]
    ============================================================ */
    printf("\nTeste 4: Multiplicação de matriz por vetor (mat_multv)\n");
    int m2 = 2, n2 = 3;
    double **B_multv = mat_cria(m2, n2);
    B_multv[0][0] = 1; B_multv[0][1] = 2; B_multv[0][2] = 3;
    B_multv[1][0] = 4; B_multv[1][1] = 5; B_multv[1][2] = 6;
    
    double v_mult[] = {1, 1, 1};  // Vetor de dimensão n2
    double *w_mult = vet_cria(m2); // Resultado de dimensão m2
    
    mat_multv(m2, n2, B_multv, v_mult, w_mult);
    
    printf("Matriz B_multv:\n");
    mat_imprime(m2, n2, B_multv);
    printf("Vetor v_mult:\n");
    vet_imprime(n2, v_mult);
    printf("Resultado w_mult:\n");
    vet_imprime(m2, w_mult);
    
    mat_libera(m2, B_multv);
    vet_libera(w_mult);

    /* ============================================================
       Teste 5: Multiplicação de matriz por matriz (mat_multm)
       - Calcula o produto de C (2x3) por D (3x2), resultando em E (2x2)
         Exemplo:
         C = [ [1,2,3],
               [4,5,6] ]
         D = [ [1,2],
               [3,4],
               [5,6] ]
         E = [ [22,28],
               [49,64] ]
    ============================================================ */
    printf("\nTeste 5: Multiplicação de matriz por matriz (mat_multm)\n");
    int m3 = 2, n3 = 3, q3 = 2;
    double **C = mat_cria(m3, n3);
    double **D = mat_cria(n3, q3);
    double **E = mat_cria(m3, q3);
    
    // Preenchendo matriz C
    C[0][0] = 1; C[0][1] = 2; C[0][2] = 3;
    C[1][0] = 4; C[1][1] = 5; C[1][2] = 6;
    
    // Preenchendo matriz D
    D[0][0] = 1; D[0][1] = 2;
    D[1][0] = 3; D[1][1] = 4;
    D[2][0] = 5; D[2][1] = 6;
    
    mat_multm(m3, n3, q3, C, D, E);
    
    printf("Matriz C:\n");
    mat_imprime(m3, n3, C);
    printf("Matriz D:\n");
    mat_imprime(n3, q3, D);
    printf("Produto E = C x D:\n");
    mat_imprime(m3, q3, E);
    
    mat_libera(m3, C);
    mat_libera(n3, D);
    mat_libera(m3, E);

    /* ============================================================
       Teste 6: Produto escalar (vet_escalar)
       - Calcula o produto escalar entre dois vetores
         Exemplo: [1,2,3] . [4,5,6] = 32
    ============================================================ */
    printf("\nTeste 6: Produto escalar (vet_escalar)\n");
    int n4 = 3;
    double v1[] = {1, 2, 3};
    double v2[] = {4, 5, 6};
    double dot = vet_escalar(n4, v1, v2);
    printf("Produto escalar entre [1,2,3] e [4,5,6]: %lf\n", dot);

    /* ============================================================
       Teste 7: Norma-2 do vetor (vet_norma2)
       - Calcula a norma-2 do vetor [3,4] (espera-se 5.0)
    ============================================================ */
    printf("\nTeste 7: Norma-2 (vet_norma2)\n");
    double v3[] = {3, 4};
    double norma = vet_norma2(2, v3);
    printf("Norma-2 do vetor [3,4]: %lf\n", norma);

    /* ============================================================
       Teste 8: Comparação de vetores (vet_iguais)
       - Verifica se dois vetores são iguais considerando uma tolerância
    ============================================================ */
    printf("\nTeste 8: Comparação de vetores (vet_iguais)\n");
    double v4[] = {1.0, 2.0, 3.0};
    double v5[] = {1.0, 2.0, 3.0};
    double tol = 0.0001;
    int iguais = vet_iguais(3, v4, v5, tol);
    printf("Comparação entre [1,2,3] e [1,2,3] com tol = %.4lf: %s\n", tol, iguais ? "iguais" : "diferentes");
    
    // Modificando o último elemento para testar a tolerância
    v5[2] = 3.0002;
    iguais = vet_iguais(3, v4, v5, tol);
    printf("Comparação entre [1,2,3] e [1,2,3.0002] com tol = %.4lf: %s\n", tol, iguais ? "iguais" : "diferentes");
    tol = 0.001;
    iguais = vet_iguais(3, v4, v5, tol);
    printf("Comparação entre [1,2,3] e [1,2,3.0002] com tol = %.4lf: %s\n", tol, iguais ? "iguais" : "diferentes");

    /* ============================================================
       Teste 9: Multiplicação de vetor por escalar (vet_mults)
       - Multiplica cada elemento do vetor por um escalar
         Exemplo: [1,2,3] * 2 = [2,4,6]
    ============================================================ */
    printf("\nTeste 9: Multiplicação de vetor por escalar (vet_mults)\n");
    int n5 = 3;
    double v6[] = {1, 2, 3};
    double s = 2.0;
    double *w6 = vet_cria(n5);
    vet_mults(n5, v6, s, w6);
    printf("Vetor original: ");
    vet_imprime(n5, v6);
    printf("Resultado da multiplicação por %.2lf: ", s);
    vet_imprime(n5, w6);
    
    vet_libera(w6);

    return 0;
}
