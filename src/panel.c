#include <stdio.h>
#include <string.h>
//
#include "../include/rsa_module.h"
#include "../include/panel.h"

int main(){
	_Bool loop = 1;

	while(loop){ //Loop principal
		main_panel();
		loop = choose();
	}

	return 0;
}

void cleanup_func(char **p){ free(*p); }

void main_panel(){
    	fputs("\033[2J\033[H", stdout);
	fputs("======== MdRSA ========\n", stdout);
	fputs("[1] Gerar chave publica\n", stdout);
	fputs("[2] Encriptar\n", stdout);
	fputs("[3] Desencriptar\n", stdout);
	fputs("[4] Sair\n", stdout);
	fputs("=======================\n", stdout);
}

_Bool choose(){
	list_t alfabeto;
        char opt;
	AUTOFREE char *buffer = NULL; 
        buffer = malloc(2);

	list_create(&alfabeto);
	init(alfabeto);

        fgets(buffer, 1, stdin);
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
			panel_decrypt();
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
	unsigned int primo_1, primo_2, relativo;
	_Bool status;

	printf("Digite um par de primos e em seguida, um numero relativamente primo a (p-1)*(q-1)\n");
	printf("Primo 1: ");
	scanf("%i", &primo_1);
	printf("Primo 2: ");
	scanf("%i", &primo_2);
	printf("Relativamente primo: ");
	scanf("%i", &relativo);

        //status = public_key(primo_1, primo_2, relativo);

	if(status)
		printf("Chave gerada com sucesso!\n");
	else
		printf("Erro! Verifique sua entrada!\n");

	getc();getc();
}

void panel_encrypt(list_t alfabeto){
	_Bool status;
	AUTOFREE char *buffer = NULL;
	AUTOFREE char *chave = NULL;

	buffer = malloc(LEN);
	chave = malloc(LEN);

	fputs("Digite a mensagem: ", stdout);
	fgets(buffer, LEN, stdin);

	fputs("Digite a chave publica: ", stdout);
	fgets(chave, LEN, stdin);

	buffer[strlen(buffer) - 1] = '\0';
	chave[strlen(chave) - 1] = '\0';

	//status = encrypt(buffer, chave, alfabeto);

	if(status)
		fputs("Mensagem encriptada com sucesso!\n", stdout);
	else
		fputs("Erro ao encriptar!\n", stdout);

	getc();
}

void panel_decrypt(){
	_Bool status = 1;
	AUTOFREE char *buffer = NULL;
	AUTOFREE char *chave = NULL;

	buffer = malloc(LEN);
	chave = malloc(LEN);

	fputs("Digite a mensagem: ", stdout);
	fgets(buffer, LEN, stdin);

	fputs("Digite os numeros que compoe a chave privada(separados por espaco): ", stdout);
	fgets(chave, LEN, stdin);

	buffer[strlen(buffer) - 1] = '\0';
	chave[strlen(chave) - 1] = '\0';

	//status = decrypt(buffer, chave);

	if(status)
		fputs("Mensagem desencriptada com sucesso!\n" stdout);
	else
		fputs("Erro ao desencriptar!\n", stdout);

	getc();
}
