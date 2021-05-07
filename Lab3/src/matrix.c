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

Matrix mat_inv(Matrix mat, char *name)
{
    return NULL;
}

Matrix mat_sup(Matrix mat, int a, int b, char *name)
{
    if (a > mat->a - 1 || b > mat->b - 1)
    {
        printf("Os valores passados excedem os limites da matriz");
        return NULL;
    }
    Matrix new_mat = mat_zeros(mat->a - 1, mat->b - 1, name);
    int aux_a = 0, aux_b = 0;

    for (int i = 0; i < new_mat->a; i++) //linhas
    {
        if (i == a)
            aux_a = 1;
        for (int j = 0; j < new_mat->b; j++) //colunas
        {
            if (j >= b)
                aux_b = 1;
            else
                aux_b = 0;
            new_mat->data[i][j] = mat->data[i + aux_a][j + aux_b];
        }
    }
    return new_mat;
}
double mat_det(Matrix mat)
{
    if (mat->a != mat->b)
    {
        printf("A matriz deve ser quadrada.");
        exit(1);
    }
    else if (mat->a >= 5)
    {
        printf("Esta funcao se limita ao calculo de determinante de uma matriz 4x4.");
        exit(1);
    }
    else
    {
        double det = 0;
        switch (mat->a)
        {
        case 1:
            det = mat->data[0][0];
            return det;
            break;
        case 2:
            det = mat->data[0][0]*mat->data[1][1]-mat->data[1][0]*mat->data[0][1];
            return det;
            break;
        case 3: 
            // Regra de Sarrus
            det = mat->data[0][0]*mat->data[1][1]*mat->data[2][2]
                 + mat->data[0][0]*mat->data[1][2]*mat->data[2][0]
                 + mat->data[2][1]*mat->data[1][0]*mat->data[0][2]
                 - mat->data[2][1]*mat->data[1][1]*mat->data[0][2]
                 - mat->data[1][0]*mat->data[0][1]*mat->data[2][2]
                 - mat->data[2][1]*mat->data[1][2]*mat->data[0][0];
            return det;
            break;
        default:
            // Teorema de Laplace
            for(int i = 0; i < mat->a; i++)
                det += mat->data[0][i] * mat_cofactor(mat, 0, i);
            break;
            return det;
        }
    }
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

double mat_cofactor(Matrix mat, int a, int b)
{
    if (a > mat->a || b > mat->b)
    {
        printf("O endereco do cofator excede o tamanho da matriz.");
        exit(1);
    }
    else if (mat->a != mat->b)
    {
        printf("A matriz deve ser quadrada.");
        exit(1);
    }
    else if (mat->a >= 5)
    {
        printf("Esta funcao se limita ao calculo de cofatores de uma matriz 4x4.");
        exit(1);
    }
    else
    {
        //Encontra a menor principal
        Matrix new_mat = mat_sup(mat, a, b, "cofactor");
        //calcula o det
        double det = mat_det(new_mat);
        //retorna o cofator
        mat_delete(new_mat);
        return det;
    }
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
