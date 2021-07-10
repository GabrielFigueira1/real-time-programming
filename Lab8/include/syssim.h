#ifndef SYSSIM_H
#define SYSSIM_H
#include "matrix.h"

/*
   Inicia as threads e mutexes da simulacao
*/
void run_simulation();
/*
   Thread que calcula a referencia a cada 50ms
*/
void *thr_reference();

/*
   Thread que calcula Ym e Xm a cada 30ms
*/
void *thr_ref_model();

/*
   Thread que calcula o controlador a cada 30ms
*/
void *thr_control();

/*
   Thread que calcula u 20ms
*/
void *thr_lin();

/*
   Thread que calcula y a cada 10ms
*/
void *thr_robot();

#endif