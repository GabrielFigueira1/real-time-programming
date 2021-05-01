#include <stdio.h>
#include "dstring.h"

int main()
{   
    // Criacao de novas strings
    dstring str1 = str_new("Esta eh uma string.");
    dstring str2 = str_new("Aqui estah outra string!");
    
    str_print(str1);
    str_print(str2);

    // Copia de strings
    str1 = str_copy(str2);
    printf("\nString copiada:\n");
    str_print(str1);

    str_free(str1);
    str_free(str2);
    // Concatenacao
    dstring str3 = str_new("Hello ");
    dstring str4 = str_new("World!");

    dstring str5 = str_concat(str3, str4);
    printf("\nString concatenada:\n");
    str_print(str5);

    // Tamanho da string
    printf("Tamanho da string acima: %d\n", str_lenght(str5));

    // Teste do macro $
    printf("\nTeste do macro:\n");
    printf("%s\n", $(str5));
}
