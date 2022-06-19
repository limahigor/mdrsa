#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//
#include "../include/rsa_module.h"
#include "../include/panel.h"

int main(){
	list_t alfabeto;
	_Bool loop = 1;

	list_create(&alfabeto);
	init(alfabeto);

	while(loop){ //Loop principal
		main_panel();
		loop = choose(alfabeto);
	}

	return 0;
}

void cleanup_func(char **p){ free(*p); }

void main_panel(){
    fputs("\033[2J\033[H", stdout);
	fputs("========== MdRSA ==========\n", stdout);
	fputs("[1] Gerar chave publica\n", stdout);
	fputs("[2] Encriptar\n", stdout);
	fputs("[3] Desencriptar\n", stdout);
	fputs("[4] Sair\n", stdout);
	fputs("===========================\n", stdout);
}

_Bool choose(list_t alfabeto){
	char opt;
	AUTOFREE char *buffer = NULL; 
	buffer = malloc(2);

	fgets(buffer, 3, stdin);
	buffer[1] = '\0';
	opt = *buffer;

	switch(opt){
		case '1':
			panel_key();
			return 1;
			break;
		case '2':
			panel_encrypt(alfabeto);
			return 1;
			break;
		case '3':
			panel_decrypt(alfabeto);
			return 1;
			break;
		case '4':
			fputs("Saindo...\n", stdout);
			return 0;
			break;
		default:
			fputs("Opcao invalida!\n", stdout);
			fputs("Aperte qualquer tecla para continuar...\n", stdout);
			return 1;
			break;
	}
}	
	
void panel_key(){
	unsigned int count = 0;
	_Bool status;

	int *num_key;
	num_key = malloc(sizeof(int) * 3);

	AUTOFREE char *chave = NULL,
				  *copy = NULL,
				  *str = NULL;

	chave = malloc(LEN);

	fputs("\033[2J\033[H", stdout);
	fputs("===== Gen Public  Key =====\n", stdout);
	fputs("Uso: Digite dois primos e\n"
		  "um numero coprimo a \n"
		  "(p-1)*(q-1), separados por\n"
		  "por espaco.\n"
		  "Ex.: 7 11 49\n"
		  "Obs.: Essa eh sua chave\n"
		  "privada, guarde com cuidado\n", stdout);
	fputs("===========================\n", stdout);

	printf("Chave: ", stdout);
	fgets(chave, LEN, stdin);
	chave[strlen(chave) - 1] = '\0';

	if(!(str_int(chave, num_key, 3))){
		fputs("Erro: verifique sua entrada\n", stdout);
		return;
	}

    status = public_key(*(num_key + 0), *(num_key + 1), *(num_key + 2));

	if(status)
		printf("Chave gerada com sucesso!\n");
	else
		printf("Erro! Verifique sua entrada!\n");

	getchar();
	free(num_key);
}

void panel_encrypt(list_t alfabeto){
	_Bool status;
	AUTOFREE char *buffer = NULL,
		 		  *chave = NULL;

	buffer = malloc(LEN);
	chave = malloc(LEN);

	fputs("\033[2J\033[H", stdout);
	fputs("========= Encrypt =========\n", stdout);
	fputs("Uso: Digite a mensagem e,\n"
		  "depois, sua chave publica.\n"
		  "Ex.: Mensagem: Ola\n"
		  "     Chave: 17 28\n"
		  "Obs.: A chave deve estar\n"
		  "separada por espaco.\n", stdout);
	fputs("===========================\n", stdout);

	fputs("Digite a mensagem: ", stdout);
	fgets(buffer, LEN, stdin);

	fputs("Digite a chave: ", stdout);
	fgets(chave, LEN, stdin);

	buffer[strlen(buffer) - 1] = '\0';
	chave[strlen(chave) - 1] = '\0';

	printf("t:%s\n", buffer);

	status = encrypt(buffer, chave, alfabeto);

	if(status)
		fputs("Mensagem encriptada com sucesso!\n", stdout);
	else
		fputs("Erro ao encriptar!\n", stdout);

	getchar();
}

void panel_decrypt(list_t alfabeto){
	_Bool status = 1;
	AUTOFREE char *buffer = NULL,
				  *chave = NULL;

	buffer = malloc(LEN);
	chave = malloc(LEN);

	fputs("\033[2J\033[H", stdout);
	fputs("========= Decrypt =========\n", stdout);
	fputs("Uso: Digite a mensagem\n"
		  "encriptada e, depois,\n"
		  "sua chave privada.\n"
		  "Ex.: Mensagem: 4 8 7\n"
		  "     Chave: 7 11 49\n"
		  "Obs.: A chave deve estar\n"
		  "separada por espaco.\n", stdout);
	fputs("===========================\n", stdout);

	fputs("Digite a mensagem: ", stdout);
	fgets(buffer, LEN, stdin);

	fputs("Digite a chave: ", stdout);
	fgets(chave, LEN, stdin);

	buffer[strlen(buffer) - 1] = '\0';
	chave[strlen(chave) - 1] = '\0';

	status = decrypt(buffer, chave, alfabeto);

	if(status)
		fputs("Mensagem desencriptada com sucesso!\n", stdout);
	else
		fputs("Erro ao desencriptar!\n", stdout);

	getchar();
}

int str_int(char *string, int *array, int qnt){
	AUTOFREE char *copy = NULL,
				  *str = NULL;

	char *state = NULL;
	unsigned int count = 0;

	if(!(copy = strdup(string))){
	    perror("Erro: verifique sua entrada!");
	    getchar();
	    return 0;
  	}

	str = strtok_r(copy, " ", &state);
  	while(str){
	    int verifica = 0;

	    for(int c = 0; c < strlen(str); c++)
	    	verifica = isdigit(str[c]);

	    if(verifica){
	    	*(array + count) = atoi(str);
	    	count++;
	    }

	    str = strtok_r( NULL, " ", &state);
  	}

  	if(count < qnt){
  		printf("Erro! Verifique sua entrada!");
  		getchar();
  		free(array);
	    return 0;
	}

	return 1;
}