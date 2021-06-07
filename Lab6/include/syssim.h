#ifndef SYSSIM_H
#define SYSSIM_H
#include "matrix.h"

/* Gera um sinal f(kT), T eh timestep e range eh o valor maximo de kT */
double *generate_time(double timestep, double range);

/* Retorna a matriz U de acordo com o instante passado */
Matrix create_u(int i);

/* Cria um matriz xdot para cada k 
   Executa o produto com a matriz U*/
//Descontinuada
Matrix *create_xdot(Matrix *u, double *time);

/* Cria um matriz X para cada k 
   Integra os valores de xdot*/
//Descontinuada
Matrix *create_x(Matrix *xdot, double *time);

/*
   Executa a simulacao com multithread
*/
void run_multithread_simulation();

/*
   Executa a simulacao single thread do laboratorio 5
*/
void run_simulation();

/*
   Escreve os dados de saida em um arquivo de texto
   Apenas para a simulacao single thread
*/
void write_data(double *time, Matrix *u, Matrix *x);

#endif