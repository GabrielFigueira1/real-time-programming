#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "integral.h"
#include "matrix.h"
#include "syssim.h"
#include "math.h"

/*
pthread_mutex_t msglock = PTHREAD_MUTEX_INITIALIZER;

int i = 0;

void *f1(void* arg)
{
    pthread_mutex_lock(&msglock);
    while(i<20) {
        
        printf("Thread Pair: %d\n", i);
        i++;
        
    }
    pthread_mutex_unlock(&msglock);
    
}
void *f2(void* arg)
{
    while(i<20) {
        pthread_mutex_lock(&msglock);
        printf("Thread Odd: %d\n", i);
        i++;
        pthread_mutex_unlock(&msglock);
    }
}
*/
int main()
{
    /*
    pthread_t t1, t2;
    pthread_create(&t1, NULL, f1, 1);
    pthread_create(&t2, NULL, f2, 2);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    */
    /*
    double *t = generate_time(0.1, 20);
    Matrix *u = create_u(t);
    Matrix *xdot = create_xdot(u, t);
    Matrix *x = create_x(xdot, t);

    write_data(t, u, x);
    */
    //printf("t  u1  u2    xc   yc    teta\n");
    //run_simulation();    
    run_multithread_simulation();    

    return 0;
}
