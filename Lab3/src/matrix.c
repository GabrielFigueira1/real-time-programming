#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"

/*
– Definição (tipo) da ADT (Matrix).
– Criação de matrizes.
– Soma, subtração e multiplicação de duas matrizes.
– Soma, subtração e multiplicação de uma matriz por escalar .
– Matriz transposta.
– Determinante de uma matriz quadrada.
– Inversão de uma matriz.
*/
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
    new_mat->data = calloc(a, sizeof(double *));

    //Para cada linha, e feita a alocacao de uma coluna
    for (int i = 0; i < a; i++)
    {
        new_mat->data[i] = calloc(b, sizeof(double));
    }

    new_mat->a = a; //linhas
    new_mat->b = b; //colunas
    new_mat->name = name;
    return new_mat;
}
Matrix mat_ones(int a, int b, char *name)
{
    //Gera uma nova matriz de zeros
    Matrix new_mat = mat_zeros(a, b, name);

    //Muda todos os valores para um;
    for (int i = 0; i < new_mat->b; i++) //colunas
    {
        for (int j = 0; j < new_mat->a; j++) //linhas
        {
            new_mat->data[i][j] = 1;
        }
    }
    return new_mat;
}
Matrix mat_identity(int a, int b, char *name)
{
    //Gera uma nova matriz de zeros
    Matrix new_mat = mat_zeros(a, b, name);

    if (a != b)
    {
        printf("A matriz deve ser quadrada.\n");
        return NULL;
    }
    //Muda todos os valores da diagonal para um;
    for (int i = 0; i < new_mat->b; i++) //colunas
        new_mat->data[i][i] = 1;

    return new_mat;
}
void mat_delete(Matrix mat)
{
    for (int i = 0; i < mat->a; i++)
    {
        free(mat->data[i]);
    }
    free(mat->data);
    free(mat);
}
void mat_display(Matrix mat)
{

    if (mat == NULL)
    {
        printf("Matriz nula\n");
    }
    else
        printf("%s\n", mat->name);
    {
        for (int i = 0; i < mat->b; i++) //colunas
        {
            for (int j = 0; j < mat->a; j++) //linhas
            {
                printf("%.3lf  ", mat->data[i][j]);
            }
            printf("\n");
        }
    }
}
