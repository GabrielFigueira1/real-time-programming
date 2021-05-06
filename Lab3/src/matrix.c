#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"

struct Matrix
{
    int a, b;
    double **data;
    char *name;
};

Matrix mat_zeros(int a, int b, char *name)
{
    Matrix new_mat = malloc(sizeof(Matrix));

    //Aloca memeoria para as linhas
    new_mat->data = calloc(a, sizeof(double*));

    //Para cada linha, e feita a alocacao de uma coluna 
    for (int i = 0; i < a; i++)
    {
        new_mat->data[i] = calloc(b, sizeof(double));
    }

    new_mat->data[0][0] = 1;
    new_mat->data[0][1] = 2;
    new_mat->data[1][0] = 3;
    new_mat->data[1][1] = 4;
    new_mat->data[4][2] = 33;

    new_mat->a = a; //linhas
    new_mat->b = b; //colunas
    new_mat->name = name;
    return new_mat;
}
Matrix mat_ones()
{

}
Matrix mat_identity()
{

}
Matrix mat_delete(Matrix mat)
{
}
void mat_display(Matrix mat)
{
    
    if (mat == NULL)
    {
        printf("Matriz nula\n");
    }
    else
    {
        int j = 0;
        for (int i = 0; i < mat->b; i++)    //colunas
        {
            for (j = 0; j < mat->a; j++)    //linhas
            {
                printf("%.3lf  ", mat->data[i][j]);
            }
            printf("\n");
        }
    }
}
