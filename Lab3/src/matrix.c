#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"

/*
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
    for (int i = 0; i < new_mat->a; i++) //linhas
    {
        for (int j = 0; j < new_mat->b; j++) //colunas
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
Matrix mat_sum(Matrix mat1, Matrix mat2, char *name)
{
    //Verifica se as matrizes possum o mesmo numero de linhas e colunas
    if (mat1->a == mat2->a && mat1->b == mat2->b)
    {
        Matrix new_mat = mat_zeros(mat1->a, mat1->b, name);
        for (int i = 0; i < new_mat->a; i++) //linhas
        {
            for (int j = 0; j < new_mat->b; j++) //colunas
            {
                new_mat->data[i][j] = mat1->data[i][j] + mat2->data[i][j];
            }
        }
        return new_mat;
    }
    else
    {
        (printf("As matrizes devem possuir a mesma ordem\n"));
        return NULL;
    }
}
Matrix mat_difference(Matrix mat1, Matrix mat2, char *name)
{
    //Verifica se as matrizes possum o mesmo numero de linhas e colunas
    if (mat1->a == mat2->a && mat1->b == mat2->b)
    {
        Matrix new_mat = mat_zeros(mat1->a, mat1->b, name);
        for (int i = 0; i < new_mat->a; i++) //linhas
        {
            for (int j = 0; j < new_mat->b; j++) //colunas
            {
                new_mat->data[i][j] = mat1->data[i][j] - mat2->data[i][j];
            }
        }
        return new_mat;
    }
    else
    {
        (printf("As matrizes devem possuir a mesma ordem\n"));
        return NULL;
    }
}
Matrix mat_product(Matrix mat1, Matrix mat2, char *name)
{
    //Testa se e possivel realizar o produto
    if (mat1->b == mat2->a)
    {
        Matrix new_mat = mat_zeros(mat1->a, mat2->b, name);
        for (int i = 0; i < mat1->a; i++) //Para cada linha de mat1
        {
            for (int j = 0; j < mat2->b; j++) //Para cada coluna de mat2
            {
                for (int k = 0; k < mat2->a; k++)
                {
                    new_mat->data[i][j] += mat1->data[i][k] * mat2->data[k][j];
                }
            }
        }
        return new_mat;
    }
    else
    {
        printf("O numero de colunas da primeira matrix deve ser igual ao numero de linhas da segunda matriz\n");
    }
    return NULL;
}

Matrix mat_s_sum(Matrix mat, double scalar, char *name)
{
    Matrix new_mat = mat_zeros(mat->a, mat->b, name);
    for (int i = 0; i < mat->a; i++) //linhas
    {
        for (int j = 0; j < mat->b; j++) //colunas
        {
            new_mat->data[i][j] = scalar + mat->data[i][j];
        }
    }
    return new_mat;
}
Matrix mat_s_product(Matrix mat, double scalar, char *name)
{
    Matrix new_mat = mat_zeros(mat->a, mat->b, name);
    for (int i = 0; i < mat->a; i++) //linhas
    {
        for (int j = 0; j < mat->b; j++) //colunas
        {
            new_mat->data[i][j] = scalar * mat->data[i][j];
        }
    }
    return new_mat;
}

Matrix mat_transp(Matrix mat, char *name)
{
    Matrix new_mat = mat_zeros(mat->b, mat->a, name);
    for (int i = 0; i < mat->a; i++) //linhas
    {
        for (int j = 0; j < mat->b; j++) //colunas
        {
            new_mat->data[j][i] = mat->data[i][j];
        }
    }
    return new_mat;
}

Matrix mat_det(Matrix mat, char *name)
{
    return NULL;
}
Matrix mat_inv(Matrix mat, char *name)
{
    return NULL;
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
        return;
    }
    printf("%s\n", mat->name);
        for (int i = 0; i < mat->a; i++) //linhas
        {
            for (int j = 0; j < mat->b; j++) //colunas
            {
                printf("%.3lf  ", mat->data[i][j]);
            }
            printf("\n");
        }
    printf("\n");
}
