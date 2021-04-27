#include <stdio.h>
#include "sum.h"
#include "subtraction.h"

int main(){
    //Variaveis que armazenam o valor passado pelo usuario
    int a, b;

    //Variaveis que armazenam o resultado da operacao
    int sum_result, subtraction_result;
    
    //Le as entradas e armazena nas variaveis
    printf("Digite o primeiro numero: \n");
    scanf("%d", a);
    printf("Digite o segundo numero: \n");
    scanf("%d", b);

    //Exibe a saida
    printf("Soma: %d\n", sum_result);
    printf("Subtacao: %d\n", subtraction_result);

    return 0;
}
