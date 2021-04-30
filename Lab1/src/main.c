#include <stdio.h>
#include "sum.h"
#include "subtraction.h"

int main(){
    //Variaveis que armazenam o valor passado pelo usuario
    double a, b;

    //Variaveis que armazenam o resultado da operacao
    double sum_result = 0, subtraction_result = 0;
    
    //Le as entradas e armazena nas variaveis
    printf("Digite o primeiro numero: \n");
    scanf("%lf", &a);
    printf("Digite o segundo numero: \n");
    scanf("%lf", &b);

    //Executa as funcoes
    sum_result = sum(a, b);
    subtraction_result = subtraction(a, b);

    //Exibe a saida
    printf("Soma: %lf\n", sum_result);
    printf("Subtacao: %lf\n", subtraction_result);

    return 0;
}
