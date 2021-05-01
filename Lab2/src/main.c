#include <stdio.h>
#include "dstring.h"

int main()
{
    char *a = "eaeqe12345"; //10
    

    dstring n = str_new(a);
    
    str_print(n);
}
