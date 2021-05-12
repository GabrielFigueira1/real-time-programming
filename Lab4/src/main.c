#include <stdio.h>
#include <stdlib.h>
#include "integral.h"
#include "math.h"

#define S(u) sin(u *M_PI / 10)

int main()
{
    //reta y=x
    double *line_a = double2array(6, 0.0, 1.0, 2.0, 3.0, 4.0, 5.0);
    D_fun line = create_fun(line_a, 6, 1, "Straight line");

    //sen(x) timestep M_PI/10
    double *sin_a = double2array(11, sin(0), S(1), S(2), S(3), S(4), S(5), S(6), S(7), S(8), S(9), S(10));
    D_fun sin1 = create_fun(sin_a, 11, M_PI / 10, "Sin wave");

    //parabola y=x^2 timestep = 0.5
    double *parable5_a = double2array(11, 0.0, 0.25, 1.0, 2.25, 4.0, 6.25, 9.0, 12.25, 16.0, 20.25, 25.0);
    D_fun parable5 = create_fun(parable5_a, 11, 0.5, "line");

    //parabola y=x^2 timestep = 0.25
    double *parable25_a = double2array(21,
                                       0.0, 0.0625, 0.25, 0.5625,
                                       1.0, 1.5625, 2.25, 3.0625,
                                       4.0, 5.0625, 6.25, 7.5625,
                                       9.0, 10.5625, 12.25, 14.0625,
                                       16.0, 18.0625, 20.25, 22.5625,
                                       25.0);
    D_fun parable25 = create_fun(parable25_a, 21, 0.25, "line");

    double integral_line = integral(line, 0, 5);
    double integral_sin = integral(sin1, 0, 10);
    double integral_parable5 = integral(parable5, 0, 10);
    double integral_parable25 = integral(parable25, 0, 20);

    //printf("Integral: %.3lf\n", integral_line);
    printf("Integral da reta: %.5lf\n", integral_line);
    printf("Integral do seno: %.5lf\n", integral_sin);
    printf("Integral da parabola 0.5: %.5lf\n", integral_parable5);
    printf("Integral da parabola 0.25: %.5lf\n", integral_parable25);

    return 0;
}
