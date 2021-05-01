#ifndef DSTRING_H
#define DSTRING_H

#define $(s) str_buffer(s)

struct dstring;
typedef struct dstring *dstring;

dstring str_new(char *str);

dstring str_copy(dstring str);

dstring str_concat(dstring str1, dstring str2);

void str_free(dstring str);

int str_lenght (dstring str);

char *str_buffer(dstring str);

void str_print(dstring str);

int cstr_len(char *str);

/* 

A manipulação de strings deve conter, ao menos:
– Definição (tipo) da ADT (dstring).
– Criação de dstrings a partir de um char*.
– Criação de dstrings a partir de tipos primitivos (char, int, long,
float etc.)
– Criação de dstrings a partir de outras dstrings
– Concatenação de dstrings
– Retorno do tamanho da dstrings
– Retorno do buffer char*
– Criar um #define $ para esta função de retorno do buffer (na prática
criando-se um operador para tranformar um dstring em um char*)

*/

#endif