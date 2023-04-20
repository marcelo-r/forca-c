#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "forca.cli.h"
#include "forca.eng.h"
#include "vetor.h"
#include "palavra.h"
#include "jogador.h"

#define WORDBANK "wordbank"

#ifdef _WIN32
	const char os = 'w';
#else
#ifdef __linux__
	const char os = 'l';
#else
#endif
#endif

void cleanit(int aviso){
	if(aviso == 1){
		printf("Aperte qualquer tecla para continuar.\n");
		getchar();
		getchar();
	}
	if(os == 'l') system("clear");
	else if (os == 'w') system("cls");
	else printf("\n-\n");
}

int menu(){
	int opcao = 0, aviso = 0;
	do{
		cleanit(aviso);
		printf("1 - Jogar\n2 - Ver Ranking\n3 - Cadastrar Palavras\n4 - Creditos\n5 - Sair\n > ");
		scanf("%d",&opcao);
		switch (opcao) {
			case 1:
				if(jogar() == 1) aviso = 1;
				else aviso = 0;
				break;
			case 2:
				menu_rank();
				aviso = 0;
				break;
			case 3:
				menu_cadastrar();
				aviso = 0;
				break;
			case 4:
				cleanit(0);
				creditos();
				aviso = 1;
				break;
			case 5:
				printf("\n!\n");
				break;
			default:
				printf("\nOpcao invalida\n");
				aviso = 1;
				break;
		}
	}while(opcao != 5);
	return 0;
}

int jogar(){
	int nivel,tamanho,cont_j = 1, raw_pontos = 0, pontos = 0, aviso = 0;
	char *word,*empty;
	char deseja = ' ';
	time_t start,end;
	double tempo = 0.0;
	FILE *arq;

	arq = fopen(WORDBANK,"rb");
	if (!arq){
		printf("Nao existe nenhuma palavra cadastrada.\n");
		return 1;
	}
	do{
		cleanit(aviso);
		aviso = 0;
		nivel = selecionar_nivel();
		word = palavra_aleatoria(arq,nivel);
		if(!word){
			printf("Nao existem palavras desse nivel\n");
			cleanit(1);
			break;
		}
		tamanho = strlen(word);
		empty = malloc(sizeof(char) * (tamanho + 1));
		if(!empty){
			printf("Erro alocacao forca\n");
			exit(1);
		}
		strcpy(empty,word);
		zera_palavra(empty,word);

		start = time(NULL);
		raw_pontos = forca(word,empty) * nivel * nivel;
		end = time(NULL);

		raw_pontos == 0 ? printf("\n--- VOCE PERDEU ---\n") : printf("\n+++ VOCE VENCEU +++\n");

		tempo = difftime(end,start);
		pontos = (int) ( (raw_pontos / tempo) * 100.0 );

		printf("A palavra era: %s\n", word);
		printf("Tempo gasto: %.0f segundos\n", tempo);
		printf("Voce fez %d pontos\n", pontos);

		free(word);
		free(empty);

		if(raw_pontos > 0){
			menu_rankear(nivel,pontos);
		}
		do {
			printf("Deseja continuar jogando? (s ou n) ");
			scanf("%s",&deseja);
			switch (deseja) {
				case 's':
					cont_j = 1;
					break;
				case 'n':
					cont_j = 0;
					break;
				default:
					printf("Opcao invalida\n");
					deseja = ' ';
			}
		} while(deseja == ' ');

	}while(cont_j == 1);
	return fclose(arq);
}

char recebe_letra(char *tentativas){
	char letra, *t;
	int valida = 0;
	getchar();
	do {
		printf("Digite uma letra: ");
		scanf("%c", &letra);
		if(check_letra(&letra) == '\0'){
			printf("Letra invalida\n");
			continue;
		}
		valida = 1;
	}while(!valida);
	t = strchr(tentativas,letra);
	if(t == NULL){
		strcat(tentativas,&letra);
		return letra;
	}
	return ' ';
}

int forca(char *word,char *empty){
	int tamanho = str_len(word), vidas = 6, numtent = 0, erros = 0, fim = 0;
	char *tentativas;
	char letra = 'a';
	tentativas = malloc(sizeof(char) * 27);
	strcpy(tentativas,"");
	if(!tentativas){
		printf("Erro alocacao tentativas\n");
		exit(1);
	}
	do {
		cleanit(0);
		imprime_forca(empty,tamanho,vidas,tentativas);
		letra = recebe_letra(tentativas);
		if( letra == ' '){
			continue;
		}
		numtent++;
		if(acha_letra(word,empty,letra) == 0){
			vidas--;
			erros++;
		}
		if(strcmp(word,empty) == 0 || vidas == 0){
			cleanit(0);
			imprime_forca(empty,tamanho,vidas,tentativas);
			fim = 1;
		}
	} while(!fim);
	free(tentativas);
	return (vidas * (numtent - erros));
}

void imprime_forca(char *empty, int tamanho, int vidas,char *tentativas){
	printf("A palavra possui %d letras\n",tamanho);
	printf("\n>  %s  <\n",empty);
	printf("\nVidas: %d\n", vidas);
	printf("Tentadas: %s\n", tentativas);
}

int selecionar_nivel(){
	int nivel = 0;
	do{
		printf("Selecione a dificuldade:\n1 - Facil\n2 - Medio\n3 - Dificil\n > ");
		scanf("%d",&nivel);
		if(nivel != 1 && nivel != 2 && nivel != 3){
			printf("Opcao invalida\n");
			nivel = 0;
		}
	}while(nivel == 0);
	return nivel;
}

void menu_cadastrar(){
	char *word;
	int nivel = 0, cont = 1,aviso = 0;
	struct Palavra *sword;
	do{
		cleanit(aviso);
		aviso = 0;
		printf("Digite a palavra ou frase que deseja cadastrar na forca:\n> ");
		word = ler_vetor(stdin);
		nivel = classificar_p(word);
		if(!nivel){
			printf("Palavra invalida.\n");
			free(word);
			continue;
		}
		sword = criar_palavra(sword,word,nivel);
		free(word);
		if(fwrite_palavra(sword,WORDBANK) == EOF){
			printf("Erro ao cadastrar, tente novamente.\n");
			aviso = 1;
			free(sword);
			continue;
		}
		printf("Palavra cadastrada com sucesso.\n");
		while(1){
			char op;
			printf("Cadastrar outra palavra (s ou n)? ");
			scanf("%s",&op);
			switch (op) {
				case 'n':
					cont = 0;
					break;
				case 's':
					aviso = 0;
					break;
				default:
					printf("\nOpcao invalida\n");
					continue;
			}
			break;
		}
		free(sword);
	}while(cont);
}

void menu_rankear(int nivel,int pontos){
	char *name;
	char *filename;
	struct Jogador *player,**arr;
	filename = arquivo_rank(nivel);
	printf("Digite seu nome: ");
	name = ler_vetor(stdin);
	player = criar_jogador(name,pontos);

	rankear(filename,player);
	cleanit(0);
	list_rank(filename);

	free(player);
	free(name);
	free(filename);
}

void menu_rank(){
	int nivel = 0;
	char *filename;
	nivel = selecionar_nivel();
	filename = arquivo_rank(nivel);
	cleanit(0);

	if( !list_rank(filename) ){
		printf("Nenhum jogador cadastrado no ranking desse nivel\n");
	}
	free(filename);
	cleanit(1);
}

int list_rank(char *filename){
	struct Jogador **arr;
	FILE *arq;
	int i = 0,len = 0;
	arq = fopen(filename,"rb");
	if(!arq){
		return 0;
	}
	arr = fread_rank(arq);
	printf(" RANKING NIVEL %c:\n  #  Pts   Nome\n",filename[strlen(filename)-1]);
	for(; i < NUM_J; i++){
		printf(" %2d- %4d  %s\n",i+1,arr[i]->pontos,arr[i]->nome);
		free(arr[i]);
	}
	free(arr);
	fclose(arq);
	return 1;
}

void creditos(){
	printf(" Desenvolvido por:\n");
	printf("  Marcelo Rolim Sobreira,\n");
	printf(" Como projeto do terceiro estagio da disciplina de\n");
	printf(" Introducao a Linguagens de Programacao,\n");
	printf(" ministrada pelo Professor Renato Atouguia.\n\n");
}
