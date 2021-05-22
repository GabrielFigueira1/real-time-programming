#ifndef SYSSIM_H
#define SYSSIM_H
#include "matrix.h"


double *generate_time(double timestep, double range);

Matrix *create_u(double *time);

Matrix *create_xdot(Matrix *u, double *time);

#endif