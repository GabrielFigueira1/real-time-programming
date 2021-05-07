#include<stdio.h>
#include "matrix.h"

int main(){
    Matrix mat_0 = mat_zeros(10, 5, "Zeros");
    Matrix mat_1 = mat_ones(5, 5, "Uns");
    Matrix mat_iden = mat_identity(5, 5, "Identidade");
    Matrix sum = mat_sum(mat_iden, mat_1, "Soma");
    Matrix dif = mat_difference(mat_iden, mat_1, "Diferenca");
    Matrix mat_test = mat_ones(3,2, "d");
    Matrix mat_test2 = mat_ones(2,3, "e");
    Matrix mat_prod = mat_product(mat_test, mat_test2, "Produto");
    /*mat_display(mat_0);
    mat_display(mat_1);
    mat_display(mat_iden);
    mat_display(sum);
    mat_display(dif);
    mat_delete(mat_0);*/
    mat_display(mat_prod);
    return 0;
}