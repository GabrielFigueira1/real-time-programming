#ifndef INTEGRAl_H
#define INTEGRAL_H

struct D_fun;
typedef struct D_fun *D_fun;

D_fun create_fun(double *fun ,int num_points, double timestep, char *name);

double *double2array(int num_points, ...);

double integral(D_fun fun, unsigned int start, unsigned int end);

#endif