#include <stdio.h>
#include <stdlib.h>
#include "integral.h"
#include "matrix.h"
#include "syssim.h"
#include "math.h"

int main()
{
    double *t = generate_time(0.1, 20);
    Matrix *u = create_u(t);
    Matrix *xdot = create_xdot(u, t);

    for(int i = 0; i <=200; i++)
        //printf("%lf\n", u[i]);
    return 0;
}
