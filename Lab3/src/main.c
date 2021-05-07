#include<stdio.h>
#include "matrix.h"

typedef enum options
{
    EXIT_PROGRAMN,
    INSERT_M1,
    INSERT_M2,
    CREATE_MAT_ZEROS,
    CREATE_MAT_ONES,
    CREATE_MAT_IDENTITY,
    DO_SUM,
    DO_DIFFERENCE,
    DO_PRODUCT,
    DO_S_SUM,
    DO_S_PRODUCT,
    TRANSP,
    INVERSE,
    REMOVE_LINE_COL,
    CALC_DET,
    CALC_COF,
    SHOW_M1,
    SHOW_M2
} option; 

option menu_option;
void open_menu();

/* Funcoes que pedem para o usuario inserir um dado atraves de scanf */
int get_a_input();
int get_b_input();
char *get_name_input();
int get_scalar_input();

int main(){
    // Matrizes usadas para a execucao de testes do programa
    Matrix M1;
    Matrix M2;
    while (1)
    {
        open_menu();
        switch (menu_option)
        {
        case EXIT_PROGRAMN:
            exit(0);
            break;
        case INSERT_M1:
            M1 = mat_insert();
        break;
        case INSERT_M2:
            M2 = mat_insert();
        break;
        case CREATE_MAT_ZEROS:
            M2 = mat_zeros(get_a_input(), get_b_input(), get_name_input());
        break;
        case CREATE_MAT_ONES:
            M2 = mat_ones(get_a_input(), get_b_input(), get_name_input());
        break;
        case CREATE_MAT_IDENTITY:
            M2 = mat_identity(get_a_input(), get_name_input());
        break;
        case DO_SUM:
            M2 = mat_sum(M1, M2, get_name_input());
        break;
        case DO_DIFFERENCE:
            M2 = mat_difference(M1, M2, get_name_input());
        break;
        case DO_PRODUCT:
            M2 = mat_product(M1, M2, get_name_input());
        break;
        case DO_S_SUM:
            M2 = mat_s_sum(M1, get_scalar_input(), get_name_input());
        break;
        case DO_S_PRODUCT:
            M2 = mat_s_product(M1, get_scalar_input(), get_name_input());
        break;
        case TRANSP:
            M2 = mat_transp(M1, get_name_input());
        break;
        case INVERSE:
            M2 = mat_inv(M1, get_name_input()); 
        break;
        case REMOVE_LINE_COL:
            int a, b;
            printf("Insira a linha a ser removida: ");
            scanf("%d", &a);
            printf("Insira a coluna a ser removida: ");
            scanf("%d", &b);
            M2 = mat_sup(M1, a, b, get_name_input());
        break;
        case CALC_DET:
            printf("Determinante de M1: %lf\n", mat_det(M1));
        break;
        case CALC_COF:
            int a, b;
            printf("Insira a linha e a coluna.\n Linha: ");
            scanf("%d", &a);
            printf("Coluna: ");
            scanf("%d", &b);
            printf("Cofator do elemento %d,%d de M1: %lf \n", a, b, mat_det(M1));
        break;
        case SHOW_M1:
            mat_display(M1);
        break;
        case SHOW_M2:
            mat_display(M2);
        break;

        default:
            printf("\nInsira uma opcao valida");
            break;
        }
    }

    Matrix mat_0 = mat_zeros(10, 5, "Zeros");
    Matrix mat_1 = mat_ones(5, 5, "Uns");
    Matrix mat_iden = mat_identity(5, "Identidade");
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
int select_mat()
{
    int sel();
    printf("Selecione onde deseja salvar a nova matriz\n");
    printf("1. M1\n");
    printf("2. M2\n");
    scanf("%d", &sel);
    if(sel == 1)
        return 1;
    else if (sel == 2)
        return 2;
    else
        printf("Opcao invalida.\n");
    exit(1);
}

int get_a_input()
{
    int a;
    printf("Insira a quantidade de linhas: ");
    scanf("%d", &a);
    return a;
}
int get_b_input()
{
    int b;
    printf("Insira a quantidade de linhas: ");
    scanf("%d", &b);
    return b;
}
char *get_name_input()
{
    char *name = malloc(sizeof(char));
    printf("Insira o nome da matriz: ");
    scanf("%s", name);
    return name;
}
int get_scalar_input()
{
    int s;
    printf("Insira o escalar: ");
    scanf("%d", &s);
    return s;
}

void open_menu()
{
    printf("Digite o numero da opcao desejada\n");
    printf("1. Inserir uma matriz m1\n");
    printf("2. Inserir uma matriz m2\n");
    printf("3. Criar matriz de zeros\n");
    printf("4. Criar matriz de uns\n");
    printf("5. Criar matriz identidade\n");
    printf("6. Soma de matrizes\n");
    printf("7. Subtracao de matrizes\n");
    printf("8. Multiplicacao de matrizes\n");
    printf("9. Soma por escalar\n");
    printf("10. Multiplicação por escalar\n");
    printf("11. Transposta\n");
    printf("12. Inversa\n\n");
    printf("13. Remover uma linha e coluna\n");
    printf("14. Determinante\n");
    printf("15. Cofator\n");
    printf("0. Encerrar programa\n\n");

    printf("Opcao: ");
    scanf("%d", &menu_option);
}
