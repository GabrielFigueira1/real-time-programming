#include <stdio.h>
#include <stdlib.h>
#include "integral.h"

int main()
{
    double *line_a = double2array(5, 0.0 ,1.0, 2.0, 3.0, 4.0); //reta x=y
    D_fun line = create_fun(line_a, 5, 1, "line");
    for (int i = 0; i < 5; i++)
    {
          double integral_line = integral(line, 0, i);
    printf("Integral %d: %.3lf\n",i, integral_line);
        //printf("%.3lf\n", line_a[i]);
    }
    double integral_line = integral(line, 0, 5);
    printf("Integral: %.3lf\n", integral_line);
    
    
    return 0;
}
