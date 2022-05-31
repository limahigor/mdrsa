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
	#ifdef OS_Windows
    	system("cls");
	#else
    	system("clear");
	#endif
    	
	printf("======== MdRSA ========\n");
	printf("[1] Gerar chave publica\n");
	printf("[2] Encriptar\n");
	printf("[3] Desencriptar\n");
	printf("[4] Sair\n");
	printf("=======================\n");
}

_Bool choose(){
	list_t alfabeto;
	unsigned char opt;

	list_create(&alfabeto);
	init(alfabeto);

	scanf(" %c", &opt);

	switch(opt){
		case '1':
			panel_chave();
			return 1;
			break;
		case '2':
			panel_encriptar(alfabeto);
			return 1;
			break;
		case '3':
			panel_desencriptar();
			return 1;
			break;
		case '4':
			printf("Saindo...\n");
			return 0;
			break;
		default:

			printf("Opcao invalida!\n");
			printf("Aperte qualquer tecla para continuar...\n");
			main_panel();
			choose();

			break;
	}
}

void panel_chave(){
	unsigned int primo_1, primo_2, relativo;
	_Bool status;

	printf("Digite um par de primos e em seguida, um numero relativamente primo a (p-1)*(q-1)\n");
	printf("Primo 1: ");
	scanf("%i", &primo_1);
	printf("Primo 2: ");
	scanf("%i", &primo_2);
	printf("Relativamente primo: ");
	scanf("%i", &relativo);

	status = gerar_chave(primo_1, primo_2, relativo);

	if(status)
		printf("Chave gerada com sucesso!\n");
	else
		printf("Erro! Verifique sua entrada!\n");

	getchar();getchar();
}

void panel_encriptar(list_t alfabeto){
	_Bool status;
	AUTOFREE char *buffer = NULL;
	AUTOFREE char *chave = NULL;

	buffer = malloc(LEN);
	chave = malloc(LEN);

	getchar();

	printf("Digite a mensagem: ");
	fgets(buffer, LEN, stdin);

	printf("Digite a chave publica: ");
	fgets(chave, LEN, stdin);

	buffer[strlen(buffer) - 1] = '\0';
	chave[strlen(chave) - 1] = '\0';

	status = encriptar(buffer, chave, alfabeto);

	if(status)
		printf("Mensagem encriptada com sucesso!\n");
	else
		printf("Erro ao encriptar!\n");

	getchar();
}

void panel_desencriptar(){
	_Bool status = 1;
	AUTOFREE char *buffer = NULL;
	AUTOFREE char *chave = NULL;

	buffer = malloc(LEN);
	chave = malloc(LEN);

	getchar();

	printf("Digite a mensagem: ");
	fgets(buffer, LEN, stdin);

	printf("Digite os numeros que compoe a chave privada(separados por espaco): ");
	fgets(chave, LEN, stdin);

	buffer[strlen(buffer) - 1] = '\0';
	chave[strlen(chave) - 1] = '\0';

	//status = desencriptar(buffer, chave);

	if(status)
		printf("Mensagem desencriptada com sucesso!\n");
	else
		printf("Erro ao desencriptar!\n");

	getchar();
}