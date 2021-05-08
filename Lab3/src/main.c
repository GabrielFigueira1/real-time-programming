#include<stdio.h>
#include<stdlib.h>
#include "matrix.h"

enum options
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
    CALC_MAT_COF,
    CALC_MAT_ADJ,
    SHOW_M1,
    SHOW_M2
}; 

int menu_option;
void open_menu();

/* Funcoes que pedem para o usuario inserir um dado atraves de scanf */
int get_a_input();
int get_b_input();
char *get_name_input();
double get_scalar_input();

int main(){
    // Matrizes usadas para a execucao de testes do programa
    Matrix M1 = NULL;
    Matrix M2 = NULL;
    int a, b;
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
            mat_display(M1);
        break;
        case INSERT_M2:
            M2 = mat_insert();
            mat_display(M2);
        break;
        case CREATE_MAT_ZEROS:
            M2 = mat_zeros(get_a_input(), get_b_input(), get_name_input());
            mat_display(M2);
        break;
        case CREATE_MAT_ONES:
            M2 = mat_ones(get_a_input(), get_b_input(), get_name_input());
            mat_display(M2);
        break;
        case CREATE_MAT_IDENTITY:
            M2 = mat_identity(get_a_input(), get_name_input());
            mat_display(M2);
        break;
        case DO_SUM:
            M2 = mat_sum(M1, M2, get_name_input());
            mat_display(M2);
        break;
        case DO_DIFFERENCE:
            M2 = mat_difference(M1, M2, get_name_input());
            mat_display(M2);
        break;
        case DO_PRODUCT:
            M2 = mat_product(M1, M2, get_name_input());
            mat_display(M2);
        break;
        case DO_S_SUM:
            M2 = mat_s_sum(M1, get_scalar_input(), get_name_input());
            mat_display(M2);
        break;
        case DO_S_PRODUCT:
            M2 = mat_s_product(M1, get_scalar_input(), get_name_input());
            mat_display(M2);
        break;
        case TRANSP:
            M2 = mat_transp(M1, get_name_input());
            mat_display(M2);
        break;
        case INVERSE:
            M2 = mat_inv(M1, get_name_input());
            mat_display(M2);
        break;
        case REMOVE_LINE_COL:
            printf("Insira a linha a ser removida: ");
            scanf("%d", &a);
            printf("Insira a coluna a ser removida: ");
            scanf("%d", &b);
            M2 = mat_sup(M1, a, b, get_name_input());
            mat_display(M2);
        break;
        case CALC_DET:
            printf("Determinante de M1: %lf\n", mat_det(M1));
            mat_display(M2);
        break;
        case CALC_COF:
            printf("Insira a linha e a coluna.\n Linha: ");
            scanf("%d", &a);
            printf("Coluna: ");
            scanf("%d", &b);
            printf("Cofator do elemento %d,%d de M1: %lf \n", a, b, mat_det(M1));
        break;
         case CALC_MAT_COF:
            M2 = mat_cof(M1);
        break;
        case CALC_MAT_ADJ:
            M2 = mat_adj(M1);
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
    printf("Insira a quantidade de colunas: ");
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
double get_scalar_input()
{
    double s;
    printf("Insira o escalar: ");
    scanf("%lf", &s);
    return s;
}

void open_menu()
{
    printf("\nDigite o numero da opcao desejada\n");
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
    printf("12. Inversa\n");
    printf("13. Remover uma linha e coluna\n");
    printf("14. Determinante\n");
    printf("15. Cofator\n");
    printf("16. Matriz de cofatores\n");
    printf("17. Adjunta\n");
    printf("18. Exibir a matriz M1\n");
    printf("19. Exibir a matriz M2\n");
    printf("0. Encerrar programa\n\n");

    printf("Opcao: ");
    scanf("%d", &menu_option);
}
