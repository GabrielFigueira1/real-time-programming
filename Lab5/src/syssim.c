#include "syssim.h"
#include "integral.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double *generate_time(double timestep, double range)
{
    double sampling_points = range / timestep;
    double *time = malloc(sampling_points * sizeof(double));

    time[0] = 0;
    for (int i = 1; i <= sampling_points; i++)
        time[i] = time[i - 1] + timestep;

    return time;
}

Matrix *create_u(double *time)
{
    double range = 20;
    double timestep = time[1];
    double sampling_points = range / timestep;

    Matrix *u = malloc(sizeof(Matrix) * sampling_points); // Uma matriz para cada ponto de amostragem
    int aux = 0;
    for (int i = 0; time[i + 1] < 10; i++)
    {
        u[i] = mat_ones(2, 1, "u");    //Matriz de uns 2x1
        u[i]->data[1][0] = 0.2 * M_PI; // [[1] [0.2*PI]]
        aux = i + 1;
    }
    for (int i = aux; time[i - 1] <= 20; i++)
    {
        u[i] = mat_ones(2, 1, "u");     //Matriz de uns 2x1
        u[i]->data[1][0] = -0.2 * M_PI; // [[1] [-0.2*PI]]
    }
    return u;
}

Matrix *create_xdot(Matrix *u, double *time)
{
    double range = 20;
    double timestep = time[1];
    double sampling_points = range / timestep;

    Matrix *xdot = malloc(sizeof(Matrix) * sampling_points);
    Matrix B = mat_zeros(3, 2, "B");
    B->data[2][1] = 1; // a32 = 1
    for (int i = 0; time[i - 1] <= 20; i++)
    {
        B->data[0][0] = sin(time[i]);
        B->data[1][0] = cos(time[i]);

        xdot[i] = mat_product(B, u[i], "xdot");
    }

    return xdot;
}

Matrix *create_x(Matrix *xdot, double *time)
{
    double range = 20;
    double timestep = time[1];
    double sampling_points = range / timestep;

    Matrix *x = malloc(sizeof(Matrix) * sampling_points);

    double *temp_fun = malloc(sizeof(double) * sampling_points);
    for (int i = 0; i < xdot[0]->a; i++)
    {
        for (int j = 0; time[j - 1] <= 20; j++)
        {
            if (x[j] == NULL)
            {
                x[j] = mat_zeros(xdot[0]->a, xdot[0]->b, "x"); //Mesmas dimensoes de xdot
            }
            for (int k = 0; time[k - 1] <= 20; k++)
            {
                temp_fun[k] = xdot[k]->data[i][0]; //Armazena os valores da x em uma double
            }
            D_fun f = create_fun(temp_fun, sampling_points + 1, timestep, "temp");
            x[j]->data[i][0] = integral(f, 0, j);
        }
    }
    return x;
}

void write_data(double *time, Matrix *u, Matrix *x)
{
    char filename[] = "data";
    FILE *fp = fopen(filename, "w");
    if (fp)
    {
        fprintf(fp, "t  u1  u2    xc   yc    teta\n");
        for (int i = 0; time[i - 1] <= 20; i++)
        {
            fprintf(fp, "%.3lf  %.3lf    %.3lf   %.3lf    %.3lf   %.3lf\n",
                                            time[i],
                                            u[i]->data[0][0],
                                            u[i]->data[1][0],
                                            x[i]->data[0][0],
                                            x[i]->data[1][0],
                                            x[i]->data[2][0]
                                            );
        }
    }
}
