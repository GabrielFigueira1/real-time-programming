#ifndef MATRIX_H
#define MATRIX_H

struct Matrix;
typedef struct Matrix *Matrix;

Matrix mat_zeros(int a, int b,char *name);
Matrix mat_ones(int a, int b, char *name);
Matrix mat_identity(int a, int b, char *name);
void mat_delete(Matrix mat);
void mat_display(Matrix mat);

#endif
