#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
//
#include "../include/rsa_module.h"
#include "../include/md_module.h"
#include "../include/panel.h"

struct alphanumeric{
	int id;
	char letra;
};

struct list_s{
	struct alphanumeric alpha;
	struct list_s *next;
};

_Bool public_key(unsigned int p, unsigned int q, unsigned int e){
	AUTOFREE char *buffer = NULL, *n_string = NULL, *e_string = NULL;
	unsigned int calc, n;
	int arq;

	if(!(isprime(p)) || !(isprime(q)))
		return 0;

	//verifica se o expoente é coprimo de (p-1)*(q-1)
	calc = ((p - 1) * (q - 1));

	if(!(mdc_euclides(calc, e) == 1))
		return 0;


	//gera o n da chave publica
	n = (p * q);

	//allloca a memoria dos buffers de string,
	//onde vão ser armazenada as chaves
	buffer 	 = malloc(LEN + 1);
	n_string = malloc(LEN - (LEN/2));
	e_string = malloc(LEN - (LEN/2));

	memset(buffer, 0, LEN + 1);

	sprintf(n_string, "%d", n);
	sprintf(e_string, "%d", e);

	strcat(buffer, n_string);
	strcat(buffer, " ");
	strcat(buffer, e_string);

	arq = open("public.txt", O_RDWR | O_CREAT, 0764);

	dprintf(arq, buffer);

	close(arq);

	return 1;
}

_Bool encrypt(char *buffer, char *chave, list_t alfabeto){
	unsigned int max, num, arq;
	unsigned char letra;

	AUTOFREE char *text_encrypted;
	text_encrypted = malloc(sizeof(int) * (LEN + 1));
	memset(text_encrypted, 0, LEN + 1);

	max = strlen(buffer); //pega o tamanho do texto a ser criptografado

	for(int c = 0; c < max; c++){
		num = get_number(buffer[c], alfabeto); //transformar letras em seus numeros correspondentes
		//fazer o calculo
		//
		//
		//*(text_encrypted + c) = num;
	}

	printf("%s\n", text_encrypted); //teste

	arq = open("encrypt.txt", O_RDWR | O_CREAT, 0764); //abre o arquivo onde vai estar o texto
	dprintf(arq, text_encrypted); //joga o texto pro arquivo
	close(arq); //fecha o arquivo
	return 1;
}

_Bool decrypt(char *buffer, char *chave, list_t alfabeto){
	unsigned int max, num, arq;
	unsigned char letra;

	char *text;
	text = malloc(LEN + 1);
	memset(text, 0, LEN + 1);

	max = strlen(buffer); //pega o tamanho do texto a ser criptografado

	for(int c = 0; c < max; c++){
		num = get_number(buffer[c], alfabeto); //transformar letras em seus numeros correspondentes
		//fazer o calculo
		//
		//
		letra = get_letter(num, alfabeto); //transfomar numeros em suas letras correspondetes
		*(text + c) = letra; //joga cada letra pra string que compoe o texto criptografado
	}

	printf("%s\n", text); //teste

	arq = open("decrypt.txt", O_RDWR | O_CREAT, 0764); //abre o arquivo pra onde o texto vai
	dprintf(arq, text); //joga o texto pro arquivo
	close(arq); //fecha o arquivo
	return 1;
}

void init(list_t alfabeto){
	list_t temp;
	temp = alfabeto;

	for(int c = 2; c <= 28; c++){
		list_t aux;

		temp->alpha.id = c;
		if(c == 28)
			temp->alpha.letra = 32;
		else
			temp->alpha.letra = 63 + c;

		list_create(&aux);
		temp->next = aux;
		temp = temp->next;
	}
}

void list_destroy(list_t list){
	while(list->next != NULL){

	}
}

void list_create(list_t *list){
	list_t aux;

	if(!list){
        printf("Erro ponteiro invalido!\n");
        exit(1);
    }

	aux = (list_t)malloc(sizeof(list_t*));

	if(!aux){
        printf("Erro alocacao de memoria!\n");
        exit(1);
    }

	memset(aux, 0, sizeof(list_t*));

	*list = aux;
}

int get_number(char letra, list_t alfabeto){
	list_t aux;
	unsigned int number;

	aux = alfabeto;

	if(letra > 90)
		letra = letra - 32;

	while(aux->next != NULL){
		if(letra == aux->alpha.letra)
			return aux->alpha.id;

		aux = aux->next;
	}

	return -1;
}

int get_letter(int num, list_t alfabeto){
	list_t aux;
	unsigned int number;

	aux = alfabeto;

	if(num < 2)
		return -1;

	if(num > 28)
		return -1;

	while(aux->next != NULL){
		if(num == aux->alpha.id)
			return aux->alpha.letra;

		aux = aux->next;
	}

	return -1;
}