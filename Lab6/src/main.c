#include <stdio.h>
#include <stdlib.h>
#include "integral.h"
#include "matrix.h"
#include "syssim.h"
#include "math.h"

int main()
{
    /*
    double *t = generate_time(0.1, 20);
    Matrix *u = create_u(t);
    Matrix *xdot = create_xdot(u, t);
    Matrix *x = create_x(xdot, t);

    write_data(t, u, x);
    */
   printf("t  u1  u2    xc   yc    teta\n");
    run_simulation();    

    return 0;
}
