#ifndef SYSSIM_H
#define SYSSIM_H
#include "matrix.h"

/* Gera um sinal f(kT), T eh timestep e range eh o valor maximo de kT */
double *generate_time(double timestep, double range);

/* Cria um matriz U para cada k */
Matrix *create_u(double *time);

/* Cria um matriz xdot para cada k 
   Executa o produto com a matriz U*/
Matrix *create_xdot(Matrix *u, double *time);

/* Cria um matriz X para cada k 
   Integra os valores de xdot*/
Matrix *create_x(Matrix *xdot, double *time);

void write_data(double *time, Matrix *u, Matrix *x);

#endif