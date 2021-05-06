#include<stdio.h>
#include "matrix.h"

int main(){

    printf("Hi\n");

    Matrix mat_0 = mat_zeros(5, 5, "Zeros");
    Matrix mat_1 = mat_ones(5, 5, "Uns");
    Matrix mat_iden = mat_identity(5, 5, "Identidade");
    mat_display(mat_0);
    mat_display(mat_1);
    mat_display(mat_iden);
    mat_delete(mat_0);
    return 0;
}