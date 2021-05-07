#ifndef MATRIX_H
#define MATRIX_H

struct Matrix;
typedef struct Matrix *Matrix;

/* Construtores */

/* Retorna uma matriz de zeros de tamanho axb. */
Matrix mat_zeros(int a, int b,char *name);
/* Retorna uma matriz de uns de tamanho axb. */
Matrix mat_ones(int a, int b, char *name);
/* Retorna uma matriz identidade de tamanho axb. */
Matrix mat_identity(int a, int b, char *name);
/* Retorna a soma de duas matrizes.
   As matrizes devem ter a mesma dimensao. */
Matrix mat_sum(Matrix mat1, Matrix mat2, char *name);
/* Retorna a diferenca de duas matrizes.
   As matrizes devem ter a mesma dimensao. */
Matrix mat_difference(Matrix mat1, Matrix mat2, char *name);
/* Retorna o produto de duas matrizes. */
Matrix mat_product(Matrix mat1, Matrix mat2, char *name);
/* Retorna uma matriz com o resultado da soma de um
   escalar em todos os elementos da matriz passada. */
Matrix mat_s_sum(Matrix mat, double scalar,char *name);
/* Retorna uma matriz com o resultado do produto escalar
   da matriz e o valor passado. */
Matrix mat_s_product(Matrix mat, double scalar, char *name);
/* Retorna a matriz transposta. */
Matrix mat_transp(Matrix mat, char *name);
/* Retorna o determinante da matriz.*/
Matrix mat_det(Matrix mat, char *name);
/* Retorna a inversa da matriz. */
Matrix mat_inv(Matrix mat, char *name);
/* Retorna uma matriz com a linha e a coluna escolhida removidas. */
Matrix mat_sup(Matrix mat, int a, int b, char *name);

/* Destrutores */

/* Destroi a matriz. */
void mat_delete(Matrix mat);

/* Outros */

/* Retorna o cofator associado ao elemento ab da matriz. */
double cofactor(Matrix mat, int a, int b);
/* Imprime a matriz no terminal. */
void mat_display(Matrix mat);

#endif
