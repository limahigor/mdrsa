#ifndef RSA_MOUDULE_H
#define RSA_MOUDULE_H

typedef struct list_s *list_t;

//funções de manipulação da lista encadeada
void list_create(list_t *list);
void init(list_t alfabeto);
void list_destroy(list_t list);

//funções auxiliares
int get_number(char letra, list_t alfabeto);
int get_letter(int num, list_t alfabeto);

//funções principais
_Bool gerar_chave(unsigned int p, unsigned int q, unsigned int e);
_Bool encriptar(char *buffer, char *chave, list_t alfabeto);
_Bool desencriptar(char *buffer, char *chave, list_t alfabeto);

#endif