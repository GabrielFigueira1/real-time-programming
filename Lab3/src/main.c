#include<stdio.h>
#include "matrix.h"

int main(){

    printf("Hi\n");

    Matrix mat = mat_zeros(5, 5, "qwe");
    mat_display(mat);
    return 0;
}