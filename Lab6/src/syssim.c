#include "syssim.h"
#include "integral.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>

double *generate_time(double timestep, double range)
{
    double sampling_points = range / timestep;
    double *time = malloc(sampling_points * sizeof(double));

    time[0] = 0;
    for (int i = 1; i <= sampling_points; i++)
        time[i] = time[i - 1] + timestep;

    return time;
}

Matrix create_u(int i)
{
    Matrix u = mat_ones(2, 1, "u");
    if (i <= 100)
        u->data[1][0] = 0.2 * M_PI;
    else
        u->data[1][0] = -0.2 * M_PI;

    return u;
}

void write_data(double *time, Matrix *u, Matrix *x)
{
    char filename[] = "data";
    FILE *fp = fopen(filename, "w");
    if (fp)
    {
        fprintf(fp, "t  u1  u2    xc   yc    teta\n");
        for (int i = 0; time[i - 1] <= 20; i++)
        {
            fprintf(fp, "%.3lf  %.3lf    %.3lf   %.3lf    %.3lf   %.3lf\n",
                    time[i],
                    u[i]->data[0][0],
                    u[i]->data[1][0],
                    x[i]->data[0][0],
                    x[i]->data[1][0],
                    x[i]->data[2][0]);
        }
    }
}

void run_simulation()
{ //paremetros
    double range = 20;
    double timestep = 0.1;
    double sampling_points = range / timestep;

    double *t = generate_time(timestep, range);

    //Primeira matriz do produto de matrizes xdot
    Matrix xdot_a = mat_zeros(3, 2, "xdot_1");

    //Matrix xdot
    Matrix xdot = mat_zeros(3, 1, "xdot");

    Matrix x = mat_zeros(3, 1, "x");

    //Armazena as linhas de xdot
    double *xdot0_fun = malloc(sizeof(double) * sampling_points);
    double *xdot1_fun = malloc(sizeof(double) * sampling_points);
    double *xdot2_fun = malloc(sizeof(double) * sampling_points);

    for (int i = 0; t[i - 1] <= 20; i++)
    {
        //Encontra xdot
        Matrix u = create_u(i);
        xdot_a->data[0][0] = sin(x->data[2][0]);
        xdot_a->data[1][0] = cos(x->data[2][0]);
        xdot_a->data[2][1] = 1;

        xdot = mat_product(xdot_a, u, "xdot");

        //Armazena xdot em doubles para a integracao
        xdot0_fun[i] = xdot->data[0][0];
        xdot1_fun[i] = xdot->data[1][0];
        xdot2_fun[i] = xdot->data[2][0];

        //integral
        D_fun xdot0_f = create_fun(xdot0_fun, i + 1, timestep, "xdot");
        D_fun xdot1_f = create_fun(xdot1_fun, i + 1, timestep, "xdot");
        D_fun xdot2_f = create_fun(xdot2_fun, i + 1, timestep, "xdot");

        x->data[0][0] = integral(xdot0_f, 0, i);
        x->data[1][0] = integral(xdot1_f, 0, i);
        x->data[2][0] = integral(xdot2_f, 0, i);

        //y(t) = I*x(t) = x(t)
        printf("%.3lf  %.3lf    %.3lf   %.3lf    %.3lf   %.3lf\n",
               t[i],
               u->data[0][0],
               u->data[1][0],
               x->data[0][0],
               x->data[1][0],
               x->data[2][0]);
    }
}

//Multithread

pthread_mutex_t msglock = PTHREAD_MUTEX_INITIALIZER;

//Variaveis compartilhadas entre as threads
sem_t S;
sem_t t1_s;
sem_t t2_s;

Matrix x;
Matrix u;
double *t;

//Threads
void *ut()
{
    //paremetros
    double range = 20;
    double timestep = 0.1;
    double sampling_points = range / timestep;

    pthread_mutex_lock(&msglock);
    t = generate_time(timestep, range);

    //Libera thread 2
    sem_post(&S);

    //Primeira matriz do produto de matrizes xdot
    Matrix xdot_a = mat_zeros(3, 2, "xdot_1");

    //Matrix xdot
    Matrix xdot = mat_zeros(3, 1, "xdot");

    x = mat_zeros(3, 1, "x");

    pthread_mutex_unlock(&msglock);

    //Armazena as linhas de xdot
    double *xdot0_fun = malloc(sizeof(double) * sampling_points);
    double *xdot1_fun = malloc(sizeof(double) * sampling_points);
    double *xdot2_fun = malloc(sizeof(double) * sampling_points);

    for (int i = 0; t[i - 1] <= 20; i++)
    {
        //Semaforo 1 -> espera a thread 2 liberar. Ja vem em post por padrao
        sem_wait(&t1_s);
        pthread_mutex_lock(&msglock);
        //Encontra xdot
        u = create_u(i);
        xdot_a->data[0][0] = sin(x->data[2][0]);
        xdot_a->data[1][0] = cos(x->data[2][0]);
        xdot_a->data[2][1] = 1;

        xdot = mat_product(xdot_a, u, "xdot");

        //Armazena xdot em doubles para a integracao
        xdot0_fun[i] = xdot->data[0][0];
        xdot1_fun[i] = xdot->data[1][0];
        xdot2_fun[i] = xdot->data[2][0];

        //integral
        D_fun xdot0_f = create_fun(xdot0_fun, i + 1, timestep, "xdot");
        D_fun xdot1_f = create_fun(xdot1_fun, i + 1, timestep, "xdot");
        D_fun xdot2_f = create_fun(xdot2_fun, i + 1, timestep, "xdot");

        x->data[0][0] = integral(xdot0_f, 0, i);
        x->data[1][0] = integral(xdot1_f, 0, i);
        x->data[2][0] = integral(xdot2_f, 0, i);
        pthread_mutex_unlock(&msglock);
        //Acorda thread 2
        sem_post(&t2_s);
    }
}

void *yf_sim()
{
    Matrix aux = mat_zeros(3, 3, "aux");
    Matrix yf;
    sem_wait(&S);
    for (int i = 0; t[i - 1] <= 20; i++)
    {
        //Semaforo 2 -> espera thread 1 mandar sinal dentro do loop
        sem_wait(&t2_s);
        pthread_mutex_lock(&msglock);
        aux->data[0][0] = cos(x->data[2][0]);
        aux->data[1][1] = sin(x->data[2][0]);
        aux->data[2][2] = 1;

        yf = mat_sum(x, mat_product(aux, x, "a"), "yf");
        printf("%.3lf  %.3lf    %.3lf   %.3lf    %.3lf   %.3lf   %.3lf   %.3lf   %.3lf\n",
               t[i],
               u->data[0][0],
               u->data[1][0],
               x->data[0][0],
               x->data[1][0],
               x->data[2][0],
               yf->data[0][0],
               yf->data[1][0],
               yf->data[2][0]);
        pthread_mutex_unlock(&msglock);
        //Libera thread 1
        sem_post(&t1_s);
    }
}

//Funcao que chama as threads
void run_multithread_simulation()
{
    pthread_t t1, t2;
    sem_init(&t1_s, 1, 1);
    sem_init(&t2_s, 1, 0);
    pthread_create(&t1, NULL, ut, NULL);
    pthread_create(&t2, NULL, yf_sim, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
}

//Funcoes descontinuadas

Matrix *create_xdot(Matrix *u, double *time)
{
    double range = 20;
    double timestep = time[1];
    double sampling_points = range / timestep;

    Matrix *xdot = malloc(sizeof(Matrix) * sampling_points);
    Matrix B = mat_zeros(3, 2, "B");
    /*
    B->data[2][1] = 1; // a32 = 1
    for (int i = 0; time[i - 1] <= 20; i++)
    {
        B->data[0][0] = sin(time[i]);
        B->data[1][0] = cos(time[i]);

        xdot[i] = mat_product(B, u[i], "xdot");
    }
    */

    return xdot;
}

Matrix *create_x(Matrix *xdot, double *time)
{
    double range = 20;
    double timestep = time[1];
    double sampling_points = range / timestep;

    Matrix *x = malloc(sizeof(Matrix) * sampling_points);

    /*
    double *temp_fun = malloc(sizeof(double) * sampling_points);
    
    for (int i = 0; i < xdot[0]->a; i++)
    {
        for (int j = 0; time[j - 1] <= 20; j++)
        {
            if (x[j] == NULL)
            {
                x[j] = mat_zeros(xdot[0]->a, xdot[0]->b, "x"); //Mesmas dimensoes de xdot
            }
            temp_fun[j] = xdot[j]->data[i][0]; //Armazena os valores da x em uma double
            D_fun f = create_fun(temp_fun, sampling_points + 1, timestep, "temp");
            x[j]->data[i][0] = integral(f, 0, j);
        }
    }
    */
    return x;
}
