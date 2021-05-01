#include <stdlib.h>
#include "dstring.h"
#include "stdio.h"

struct dstring
{
    int size;
    char *str;
};

dstring str_new(char *str)
{
    if(str == NULL)
        return NULL;

    //Construtor
    dstring new = malloc(sizeof(dstring));

    new->size = cstr_len(str);

    //Aloca memoria para a string dentro do struct
    new->str = malloc(sizeof(char)*new->size);
    //Escreve a string dentro do novo struct
    for(int i = 0; i<new->size; i++)
    {
        new->str[i] = str[i];
    }    

    return new;
}

dstring str_copy(dstring str)
{

}

dstring str_concat(dstring str1, dstring str2)
{

}

void str_free(dstring str)
{

}

int str_lenght(dstring str)
{
    return str->size;    
}

char *str_buffer(dstring str)
{

}

void str_print(dstring str)
{
    for(int i = 0; i<str->size; i++)
    {
        printf("%c", str->str[i]);
    }    
    printf("\n");
}

int cstr_len(char *str)
{
    //Encontra o tamanho da string
    //O ultimo elemento da string eh sempre '\0'
    int size;
    for(size = 0; str[size] != '\0'; size++);

    return size;
}