#include <stdio.h>
#include "dstring.h"

int main()
{
    char *a = "03"; //10
    char *b = " O2"; //10

    dstring n = str_new(a);
    dstring m = str_new(b);
    dstring o = str_concat(m, n);
    b = $(o);

    for(int i = 0; i < 5; i++){
        printf("%c", b[i]);
    }
}
