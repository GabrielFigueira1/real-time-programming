#include "syssim.h"
#include "stdlib.h"
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
    int i = 0;
    for (i = 0; time[i + 1] < 10; i++)
    {
        u[i] = mat_ones(2, 1, "u");    //Matriz de uns 2x1
        u[i]->data[1][0] = 0.2 * M_PI; // [[1] [0.2*PI]]
    }
    for (i; time[i - 1] <= 20; i++)
    {
        u[i] = mat_ones(2, 1, "u");     //Matriz de uns 2x1
        u[i]->data[1][0] = -0.2 * M_PI; // [[1] [-0.2*PI]]
    }
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
