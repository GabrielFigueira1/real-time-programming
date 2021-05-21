#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "integral.h"

struct D_fun
{
    int num_points;
    double *fx;
    double timestep;
    char *name;
};

D_fun create_fun(double *fun, int num_points, double timestep, char *name)
{
    D_fun new_fun = malloc(sizeof(D_fun));
    new_fun->fx = malloc(num_points * sizeof(double));
    new_fun->num_points = num_points;
    new_fun->name = name;
    new_fun->timestep = timestep;

    for (int i = 0; i < num_points; i++)
    {
        new_fun->fx[i] = fun[i];
    }

    return new_fun;
}

double *double2array(int num_points, ...)
{
    double *d = malloc(num_points * sizeof(double));
    va_list ap;
    va_start(ap, num_points);

    for (int i = 0; i < num_points; i++)
    {
        d[i] = va_arg(ap, double);
    }

    return d;
}

double integral(D_fun fun, unsigned int start, unsigned int end)
{
    if (start >= end)
    {
        printf("Intervalo invalido.\n");
        return 0;
    }
    else if (start >= fun->num_points - 1)
    {
        printf("start deve ser menor que o numero de amostras da funcao menos um.\n");
        return 0;
    }
    else if (end > fun->num_points - 1)
    {
        printf("end deve ser menor ou igual que o numero de amostras da funcao menos um.\n");
        return 0;
    }
    double total = 0;

    for (int i = start; i < end; i++)
    {
        total += (fun->fx[i] + fun->fx[i + 1]) / 2 * fun->timestep; //area do trapezio
    }

    return total;
}