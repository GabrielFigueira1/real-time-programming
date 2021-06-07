#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "integral.h"
#include "matrix.h"
#include "syssim.h"
#include "math.h"


int main()
{
    //run_simulation();    
    run_multithread_simulation();    

    return 0;
}
