#ifndef INTEGRAl_H
#define INTEGRAL_H

struct D_fun;
typedef struct D_fun *D_fun;

/* Construtor do tipo necessario para usar a integracao;
   Os pontos de f(x) sao salvos em double *fx;
   O valor de timestep serve para calcular os pontos do eixo x .*/
D_fun create_fun(double *fun, int num_points, double timestep, char *name);

/* Retorna um array com os valores double passados. */
double *double2array(int num_points, ...);

/* Retorna o valor da integral de fun, calculada pela soma de Riemann.
   start e end sao os enderecos do array para comecar e terminar a integracao. */
double integral(D_fun fun, unsigned int start, unsigned int end);

#endif