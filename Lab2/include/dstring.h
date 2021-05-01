#ifndef DSTRING_H
#define DSTRING_H

#define $(s) str_buffer(s)

struct dstring;
typedef struct dstring *dstring;

/* Retorna uma nova string a partir de str */
dstring str_new(char *str);
/* Retorna uma copia de str */
dstring str_copy(dstring str);
/* Retorna uma nova string resultado da concatenacao
de str1 e str2 */
dstring str_concat(dstring str1, dstring str2);
/* Metodo destrutor */
void str_free(dstring str);
/* Retorna o numero de caracteres em str*/
int str_lenght(dstring str);
/* Retorna uma string no formato char*
Pode ser usado pelo macro $(str) */
char *str_buffer(dstring str);
/* Imprime uma string no terminal*/
void str_print(dstring str);
/* Retorna o tamanho de uma string no formato char* */
int cstr_len(char *str);

#endif