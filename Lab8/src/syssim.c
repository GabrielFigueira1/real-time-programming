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
#define REF_MODEL_PERIOD_NS 30e6 //30ms
#define REF_MODEL_PERIOD_S 0.030 //30ms

#define END_TIME_S 13 //13 segundos

struct timespec tp;
struct timespec timeout_ref;
struct timespec timeout_ref_model;

double start_time = 0;
double reference_time = 0;
double xref = 0;
double yref = 0;
double xm = 0;
double ym = 0;

//Retorna um valor em segundos atraves do struct timespec
double timespec_to_sec(struct timespec *tp)
{
    long start_s = tp->tv_sec;
    long start_ns = tp->tv_nsec;

    double current_time = ((double)start_s + (double)start_ns * 1e-9) - start_time;
    return current_time;
}
//salva o tempo de inicio do programa
void setup_time()
{
    int start = clock_gettime(CLOCK_REALTIME, &tp);
    long start_s = tp.tv_sec;
    long start_ns = tp.tv_nsec;
    start_time = (double)start_s + (double)start_ns * 1e-9;
    ;
}

//retorna o tempo atual em nanossegundos desde o inicio o programa
double get_time()
{
    int start = clock_gettime(CLOCK_REALTIME, &tp);
    long start_s = tp.tv_sec;
    long start_ns = tp.tv_nsec;

    double current_time = ((double)start_s + (double)start_ns * 1e-9) - start_time;
    return current_time;
}

//Configura o tempo de duracao de uma thread no struct timespec
void set_period(double calculated_time, int period, struct timespec *__tp)
{
    //Compensa o tempo de processamento para melhor sincronia do processo
    double new_period = (double)period * 1e-9 - (get_time() - calculated_time);
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

//Mutexes para temporizacao
pthread_mutex_t mtx_timer_reference = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mtx_timer_ref_model = PTHREAD_MUTEX_INITIALIZER;

//Mutexes
pthread_mutex_t mtx_time = PTHREAD_MUTEX_INITIALIZER;

void setup_mutexes()
{
    pthread_mutex_init(&mtx_timer_reference, NULL);
    pthread_mutex_lock(&mtx_timer_reference);

    pthread_mutex_init(&mtx_timer_ref_model, NULL);
    pthread_mutex_lock(&mtx_timer_ref_model);

    pthread_mutex_init(&mtx_time, NULL);
}

void run_simulation()
{
    setup_time();
    setup_mutexes();
    pthread_t t1, t2, t3, t4, t5;

    pthread_create(&t1, NULL, thr_reference, NULL);
    pthread_create(&t2, NULL, thr_ref_model, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
}

void *thr_reference()
{
    int k = 0;
    while ((k * REFERENCE_PERIOD_S) <= END_TIME_S)
    {
        double calculated_time = k * REFERENCE_PERIOD_S;

        //escreve o valor de tempo medido
        pthread_mutex_lock(&mtx_time);
        reference_time = get_time();
        pthread_mutex_unlock(&mtx_time);

        clock_gettime(CLOCK_REALTIME, &timeout_ref);
        set_period(calculated_time, REFERENCE_PERIOD_NS, &timeout_ref);

        //espera
        int try_wait = pthread_mutex_timedlock(&mtx_timer_reference, &timeout_ref);

        //testes
        /*
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

void *thr_ref_model()
{
    int k = 0;

    while ((k * REF_MODEL_PERIOD_S) <= END_TIME_S)
    {
        double calculated_time = k * REF_MODEL_PERIOD_S;

        pthread_mutex_lock(&mtx_time);
        if (reference_time >= 0 && reference_time < (2 * M_PI))
        {
            xref = (0.5) - (0.5) * cos(reference_time);
            yref = (0.5) * sin(reference_time);
        }
        else if (reference_time >= (2 * M_PI) && reference_time < (4 * M_PI))
        {
            xref = -(0.5) + (0.5) * cos(reference_time);
            yref = -(0.5) * sin(reference_time);
        }
        else if (reference_time < 0 || reference_time > 4 * M_PI)
        {
            xref = 0;
            yref = 0;
        }
        /*
        //Testes
        printf("xref = %lf\n", xref);
        printf("yref = %lf\n", yref);
        printf("time = %lf\n", reference_time);
        printf("k = %d\n", k);
        */

        pthread_mutex_unlock(&mtx_time);

        clock_gettime(CLOCK_REALTIME, &timeout_ref_model);
        set_period(calculated_time, REF_MODEL_PERIOD_NS, &timeout_ref_model);

        //espera
        int try_wait = pthread_mutex_timedlock(&mtx_timer_ref_model, &timeout_ref_model);
        k++;
    }
}
