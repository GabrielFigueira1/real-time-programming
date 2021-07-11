#include "syssim.h"
#include "integral.h"
#include "matrix.h"
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
#define CONTROL_PERIOD_NS 30e6 //30ms
#define CONTROL_PERIOD_S 0.030 //30ms
#define LIN_PERIOD_NS 20e6 //20ms
#define LIN_PERIOD_S 0.020 //20ms
#define ROBOT_PERIOD_NS 10e6 //10ms
#define ROBOT_PERIOD_S 0.010 //10ms

#define END_TIME_S 1 //13 segundos

struct timespec tp;
struct timespec timeout_ref;
struct timespec timeout_ref_model;
struct timespec timeout_control;
struct timespec timeout_lin;
struct timespec timeout_robot;


double start_time = 0;
double reference_time = 0;
double xref = 0;
double yref = 0;
double ymy = 0, ymx = 0;
double ymy_dot = 0, ymx_dot = 0;
double y1a = 0, y2 = 0;
double alfa1 = 1, alfa2 = 1;
double R = 0.3;

double xc = 0, yc = 0, x3 = 0;
//Matrizes
Matrix v, u, L, x_dot, x, y;

//Matrizes auxiliares
Matrix x_dot_a, y_a, y_b;

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
pthread_mutex_t mtx_timer_control = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mtx_timer_lin = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mtx_timer_robot = PTHREAD_MUTEX_INITIALIZER;

//Mutexes
pthread_mutex_t mtx_time = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mtx_ref = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mtx_v = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mtx_x = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mtx_y = PTHREAD_MUTEX_INITIALIZER;


void setup_mutexes()
{
    pthread_mutex_init(&mtx_timer_reference, NULL);
    pthread_mutex_lock(&mtx_timer_reference);

    pthread_mutex_init(&mtx_timer_ref_model, NULL);
    pthread_mutex_lock(&mtx_timer_ref_model);

    pthread_mutex_init(&mtx_timer_control, NULL);
    pthread_mutex_lock(&mtx_timer_control);
     
    pthread_mutex_init(&mtx_timer_lin, NULL);
    pthread_mutex_lock(&mtx_timer_lin);

    pthread_mutex_init(&mtx_timer_robot, NULL);
    pthread_mutex_lock(&mtx_timer_robot);

    pthread_mutex_init(&mtx_time, NULL);
    pthread_mutex_init(&mtx_ref, NULL);
    pthread_mutex_init(&mtx_v, NULL);
    pthread_mutex_init(&mtx_x, NULL);
    pthread_mutex_init(&mtx_y, NULL);
}

void setup_matrix()
{
    v = mat_zeros(2, 1, "Controlador");
    u = mat_zeros(2, 1, "ut");
    L = mat_zeros(2, 2, "L");
    x_dot = mat_zeros(3, 1, "x_dot");
    x = mat_zeros(3, 1, "x");
    y = mat_zeros(2, 1, "y");

    x_dot_a = mat_zeros(3, 2, "xdot_a");
    y_a = mat_zeros(2, 3, "y_a");
    y_b = mat_zeros(2, 1, "Y_b");

    y_a->data[0][0] = 1;
    y_a->data[1][1] = 1;
}
void run_simulation()
{
    setup_matrix();
    setup_time();
    setup_mutexes();
    pthread_t t1, t2, t3, t4, t5;

    pthread_create(&t1, NULL, thr_reference, NULL);
    pthread_create(&t2, NULL, thr_ref_model, NULL);
    pthread_create(&t3, NULL, thr_control, NULL);
    pthread_create(&t4, NULL, thr_lin, NULL);
    pthread_create(&t5, NULL, thr_robot, NULL);
    //printf("xc      yc      x3      t       t_ref");
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    pthread_join(t5, NULL);
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
        pthread_mutex_lock(&mtx_ref);
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
        pthread_mutex_unlock(&mtx_ref);
        pthread_mutex_unlock(&mtx_time);

        clock_gettime(CLOCK_REALTIME, &timeout_ref_model);
        set_period(calculated_time, REF_MODEL_PERIOD_NS, &timeout_ref_model);

        //espera
        int try_wait = pthread_mutex_timedlock(&mtx_timer_ref_model, &timeout_ref_model);
        k++;
    }
}

void *thr_control()
{
    int k = 0;

    while ((k * CONTROL_PERIOD_S) <= END_TIME_S)
    {
        double calculated_time = k * CONTROL_PERIOD_S;

        pthread_mutex_lock(&mtx_ref);
        pthread_mutex_lock(&mtx_v);
        pthread_mutex_lock(&mtx_y);
        v->data[0][0] = alfa1 * (xref - y1a);
        v->data[1][0] = alfa2 * (yref - y2);
        pthread_mutex_unlock(&mtx_y);
        pthread_mutex_unlock(&mtx_v);
        pthread_mutex_unlock(&mtx_ref);

        printf("v1 = %lf\n", v->data[0][0]);
        printf("v2 = %lf\n", v->data[1][0]);
        printf("time = %lf\n", reference_time);
        printf("k = %d\n\n", k);

        clock_gettime(CLOCK_REALTIME, &timeout_control);
        set_period(calculated_time, CONTROL_PERIOD_NS, &timeout_control);

        //espera
        int try_wait = pthread_mutex_timedlock(&mtx_timer_control, &timeout_control);
        k++;
    }
}

void *thr_lin()
{
    int k = 0;

    while ((k * LIN_PERIOD_S) <= END_TIME_S)
    {
        double calculated_time = k * LIN_PERIOD_S;

        pthread_mutex_lock(&mtx_x);
        L->data[0][0] = cos(x3);
        L->data[1][0] = sin(x3);
        L->data[0][1] = -R * (sin(x3));
        L->data[1][1] = R * (cos(x3));
        pthread_mutex_unlock(&mtx_x);

        pthread_mutex_lock(&mtx_v);
        u = mat_product(mat_inv(L, "L_inv"), v, "u");
        pthread_mutex_unlock(&mtx_v);
        /*
        printf("v1 = %lf\n", v->data[0][0]);
        printf("time = %lf\n", reference_time);
        printf("k = %d\n\n", k);
        */
        clock_gettime(CLOCK_REALTIME, &timeout_lin);
        set_period(calculated_time, LIN_PERIOD_NS, &timeout_lin);

        //espera
        int try_wait = pthread_mutex_timedlock(&mtx_timer_lin, &timeout_lin);
        k++;
    }
}

void *thr_robot()
{
    int k = 0;
    double xlast[3] = {0, 0, 0};
    double previous_time = 0, actual_time = 0;
    while ((k * ROBOT_PERIOD_S) <= END_TIME_S)
    {
        double calculated_time = k * ROBOT_PERIOD_S;

        pthread_mutex_lock(&mtx_x);
        //xdot
        x_dot_a->data[0][0] = sin(x3);
        x_dot_a->data[1][0] = cos(x3);
        x_dot_a->data[2][1] = 1;

        x_dot = mat_product(x_dot_a, u, "xdot");
        
        //integral com regra do trapezio
        actual_time = get_time();
        for (int i=0; i<3; i++)
        {
            x->data[i][0] += (xlast[i] + x_dot_a->data[i][0]) * (actual_time - previous_time) / 2;
            xlast[i] = x->data[i][0];
        }
        previous_time = actual_time;
        xc = x->data[0][0];
        yc = x->data[1][0];
        x3 = x->data[2][0];
        
        //y
        y_b->data[0][0] = R * cos(x3);
        y_b->data[1][0] = R * sin(x3);
        y = mat_sum(mat_product( y_a, x,"prod"), y_b, "y");

        pthread_mutex_lock(&mtx_y);
        y1a = y->data[0][0];
        y2 = y->data[1][0];
        pthread_mutex_unlock(&mtx_y);
        
        //imprime dados
        //printf("k = %d\n", k);
        pthread_mutex_unlock(&mtx_x);
 
        clock_gettime(CLOCK_REALTIME, &timeout_robot);
        set_period(calculated_time, ROBOT_PERIOD_NS, &timeout_robot);

        //espera
        int try_wait = pthread_mutex_timedlock(&mtx_timer_robot, &timeout_robot);
        k++;
    }
}