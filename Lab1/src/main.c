#include <stdio.h>
#include <stdlib.h>
#include "sum.h"
#include "subtraction.h"

void test(int a);

int main()
{
    //Variaveis que armazenam o valor passado pelo usuario
    double a, b;

    //Variaveis que armazenam o resultado da operacao
    double sum_result, subtraction_result;

    //Le as entradas e armazena nas variaveis
    printf("Digite o primeiro numero: \n");
    int item1 = scanf("%lf", &a);
    test(item1);

    printf("Digite o segundo numero: \n");
    int item2 = scanf("%lf", &b);
    test(item2);

    //Executa as funcoes

    sum_result = sum(a, b);
    subtraction_result = subtraction(a, b);

    //Exibe a saida
    printf("Soma: %.3lf\n", sum_result);
    printf("Subtacao: %.3lf\n", subtraction_result);

    return 0;
}

void test(int a)
{
    if(a == 0)
    {
        printf("Entrada invalida\n");
        exit(0);
    }
}