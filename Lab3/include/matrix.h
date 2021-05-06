#ifndef MATRIX_H
#define MATRIX_H

struct Matrix;
typedef struct Matrix *Matrix;

Matrix mat_zeros(int M, int N,char *name);
Matrix mat_ones();
Matrix mat_identity();
Matrix mat_delete(Matrix mat);
void mat_display(Matrix mat);

#endif
