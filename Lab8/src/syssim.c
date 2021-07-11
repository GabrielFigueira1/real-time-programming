#include "syssim.h"
#include "integral.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>

#define BASE_TIME_NS 10e6        //10ms em ns
#define REFERENCE_PERIOD_NS 50e6 //50ms
#define REFERENCE_PERIOD_S 0.050 //50ms

#define END_TIME_S 13 //13 segundos

double reference_time;
struct timespec tp;
struct timespec timeout_ref;

double start_time;

//salva o tempo de inicio do programa
void setup_time()
{
    int start = clock_gettime(CLOCK_REALTIME, &tp);
    long start_s = tp.tv_sec;
    long start_ns = tp.tv_nsec;

    start_time = (double)start_s + (double)start_ns * 1e-9;
}

//retorna o tempo atual em nanossegundos desde o inicio o programa
double get_time()
{
    int start = clock_gettime(CLOCK_REALTIME, &tp);
    long start_s = tp.tv_sec;
    long start_ns = tp.tv_nsec;

    double current_time = ((double)start_s + (double)start_ns * 1e-9) - start_time;
}

double timespec_to_sec(struct timespec *tp)
{
    long start_s = tp->tv_sec;
    long start_ns = tp->tv_nsec;

    double current_time = ((double)start_s + (double)start_ns * 1e-9) - start_time;
}

//Configura o tempo de duracao de uma thread no struct timespec
void set_period(double calculated_time, int period, struct timespec *__tp)
{
    //Compensa o tempo de processamento para melhor sincronia do processo
    double new_period = (double)period*1e-9 - (get_time() - calculated_time);
    new_period *= 1e9;
    period = (int)new_period;

    __tp->tv_nsec += period;

    //Verifica se tv_nsec ultrapassa o limite de 1e9
    //e faz a correcao dos valores
    if (__tp->tv_nsec >= 1e9)
    {
        __tp->tv_nsec -= 1e9;
        __tp->tv_sec += 1;
    }
}

pthread_mutex_t mtx_reference = PTHREAD_MUTEX_INITIALIZER;

void run_simulation()
{
    setup_time();
    pthread_mutex_init(&mtx_reference, NULL);
    pthread_mutex_lock(&mtx_reference);
    pthread_t t1, t2, t3, t4, t5;

    pthread_create(&t1, NULL, thr_reference, NULL);
    pthread_join(t1, NULL);
}

void *thr_reference()
{
    int k = 0;
    while ((k * REFERENCE_PERIOD_S) <= END_TIME_S)
    {
        double calculated_time = k * REFERENCE_PERIOD_S;

        //escreve o valor de tempo medido
        //colocar mutex
        reference_time = get_time();

        clock_gettime(CLOCK_REALTIME, &timeout_ref);
        set_period(calculated_time ,REFERENCE_PERIOD_NS, &timeout_ref);

        //espera
        int try_wait = pthread_mutex_timedlock(&mtx_reference, &timeout_ref);

        /*
        //testes
        printf("inicio: %.9lf\n", reference_time);
        double end = get_time();
        printf("fim: %.9lf\n", end);
        double comp_time = end - reference_time;
        printf("Tempo de computação ns: %lf\n", comp_time);
        printf("k= %d\n\n", k);
        */
        k++;
    }
}
