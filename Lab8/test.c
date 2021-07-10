#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "integral.h"
#include "matrix.h"
#include "syssim.h"
#include "math.h"

struct timespec tp;
clockid_t clk_id;

//timeout
struct timespec timeoutTime;

  clk_id = CLOCK_REALTIME;
//  clk_id = CLOCK_MONOTONIC;
//  clk_id = CLOCK_BOOTTIME;
//  clk_id = CLOCK_PROCESS_CPUTIME_ID;

#define PERIODO_1 300000000 //ms em ns
#define PERIODO_2 0.500 //ms em s

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

//executar por 100ms
void *th1(){
    printf("Thread 1\n");
    int start = clock_gettime(clk_id, &tp);
    printf("%ld\n", tp.tv_nsec);
    long start_s = tp.tv_sec;
    long start_ns = tp.tv_nsec;
    for(int i = 0; i < 10000; i++){
        
    }
    //pthread_mutex_lock(&lock);
    //Calcula o tempo de computação
    clock_gettime(CLOCK_REALTIME, &timeoutTime);
    timeoutTime.tv_nsec += PERIODO_1;
    int try_wait = pthread_mutex_timedlock(&lock, &timeoutTime);
    printf("tr: %d\n", try_wait);
    //Correcao do erro em https://stackoverflow.com/questions/47394474/pthread-cond-timedwait-ret-22-but-errno-is-success
    int end = clock_gettime(clk_id, &tp);
    float comp_time =(float) (tp.tv_sec - start_s)+(tp.tv_nsec - start_ns)*1e-9;
    printf("%ld\n", tp.tv_nsec);
    
    printf("Tempo de computação ns: %f\n", comp_time);

}

void *th2(){
    //printf("Thread 2\n");
}

int main()
{
    //run_simulation();    
    //run_multithread_simulation();    

    pthread_mutex_init(&lock, NULL);
    pthread_mutex_lock(&lock);
    pthread_t t1, t2;
    pthread_create(&t1, NULL, th1, NULL);
    pthread_create(&t2, NULL, th2, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
