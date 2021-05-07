#ifndef MATRIX_H
#define MATRIX_H

struct Matrix;
typedef struct Matrix *Matrix;

Matrix mat_zeros(int a, int b,char *name);
Matrix mat_ones(int a, int b, char *name);
Matrix mat_identity(int a, int b, char *name);
Matrix mat_sum(Matrix mat1, Matrix mat2, char *name);
Matrix mat_difference(Matrix mat1, Matrix mat2, char *name);
Matrix mat_product(Matrix mat1, Matrix mat2, char *name);
void mat_delete(Matrix mat);
void mat_display(Matrix mat);

#endif
