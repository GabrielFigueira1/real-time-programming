#include<stdio.h>
#include "matrix.h"

int main(){
    Matrix mat_0 = mat_zeros(10, 5, "Zeros");
    Matrix mat_1 = mat_ones(5, 5, "Uns");
    Matrix mat_iden = mat_identity(5, 5, "Identidade");
    Matrix sum = mat_sum(mat_iden, mat_1, "Soma");
    Matrix dif = mat_difference(mat_iden, mat_1, "Diferenca");
    Matrix mat_test = mat_ones(3,2, "test ones");
    Matrix mat_test2 = mat_ones(2,3, "test onde 2");
    Matrix mat_prod = mat_product(mat_test, mat_test2, "Produto");
    Matrix test_scalar_product = mat_s_product(mat_test, 10, "teste produto escalar");
    Matrix test_scalar_sum = mat_s_sum(mat_iden, -1, "teste soma escalar");
    Matrix tranp = mat_transp(test_scalar_product, "transposta");
    Matrix removed = mat_sup(mat_iden, 0, 0, "Sup");
    mat_display(mat_0);
    mat_display(mat_1);
    mat_display(mat_iden);
    mat_display(sum);
    mat_display(dif);
    mat_delete(mat_0);
    mat_display(mat_prod);
    mat_display(test_scalar_product);
    mat_display(test_scalar_sum);
    //mat_display(mat_test);
    //mat_display(test_scalar_product);

    //mat_display(tranp);
    //mat_display(removed);
    printf("Det: %lf", mat_cofactor(sum, 0, 0));
    return 0;
}