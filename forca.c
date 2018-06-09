#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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

int menu();
void jogar();
int selecionar_nivel();
void menu_cadastrar();
void menu_add_rank(int nivel,int pontos);
void menu_show_rank();

int forca(char *word,char *empty);
void imprime_forca(char *empty, int tamanho, int vidas,char *tentativas);
char recebe_letra(char *tentativas);
int rankear(char *filename,int nivel);

char check_letra(char *letra);
int str_len(char *word);

void cleanit(int aviso);

char *arquivo_rank(int nivel);

const char *rank = "rank";

int main() {
	srand( time(NULL) );
	NUM_P = 0;
 	for(;;){
  		if (menu() == 0) return 0;
		else return 1;
	}
}

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

int str_len(char *word){
	int len = 0;
	if(!word) return 0;
	for(; *word != '\0'; word++) if(*word != ' ') len++;
	return len;
}

int menu(){
	int opcao = 0, aviso =0;
	do{
		cleanit(aviso);
		printf("1 - Jogar\n2 - Ver Ranking\n3 - Cadastrar Palavras\n4 - Creditos\n5 - Sair\n > ");
		scanf("%d",&opcao);
		switch (opcao) {
			case 1:
				jogar();
				break;
			case 2:
				menu_show_rank();
				printf("\nEm breve\n");
				break;
			case 3:
				menu_cadastrar();
				break;
			case 4:
				// creditos();
				printf("\nBy Tora Balde\n\n");
				getchar();
				getchar();
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

void jogar(){
	int nivel,tamanho,cont_j = 1, raw_pontos = 0, pontos = 0, aviso = 0;
	char *word,*empty;
	char deseja = ' ';
	time_t start,end;
	double tempo = 0.0;
	FILE *arq;

	arq = fopen(WORDBANK,"rb");
	if (!arq){
		printf("Erro ao abrir arquivo\n");
		exit(1);
	}
	do{
		cleanit(aviso);
		aviso = 0;
		nivel = selecionar_nivel();
		word = palavra_aleatoria(arq,nivel);
		if(!word){
			printf("Nao existem palavras desse nivel\n");
			aviso = 1;
			continue;
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
			menu_add_rank(nivel,pontos);
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
	fclose(arq);
}

char check_letra(char *letra){
	if(!letra) return '\0';
	if( !((*letra >= 65 && *letra <= 90) || (*letra >= 97 && *letra <= 122) ) ) return '\0';
	return *letra;
}

char recebe_letra(char *tentativas){
	char letra, *t;
	int valida = 0;
	getchar();
	do {
		printf("Digite uma letra: ");
		scanf("%s", &letra);
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

// nivel * vidas * (tentativas - erros)
int forca(char *word,char *empty){
	int tamanho = str_len(word), vidas = 6, numtent = 0, erros = 0, fim = 0, aviso = 0;
	char *tentativas;
	char letra;
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
			printf("\nLetra já tentada\n");
			continue;
		}
		numtent++;
		if(acha_letra(word,empty,letra) == 0){
			vidas--;
			erros++;
			aviso = 0;
		}
		if(strcmp(word,empty) == 0 || vidas == 0){
			cleanit(0);
			imprime_forca(empty,tamanho,vidas,tentativas);
			fim = 1;
		}
	} while(!fim);

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
		// printf("Dificuldade: ");
		// scanf("%d", &nivel);
		nivel = selecionar_nivel();
		sword = criar_palavra(sword,word,nivel);
		if(fwrite_palavra(sword,WORDBANK) == EOF){
			printf("Erro ao cadastrar, tente novamente.\n");
			aviso = 1;
			continue;
		}
		printf("Palavra cadastrada com sucesso.\n");
		while(1){
			char op;
			printf("Cadastrar outra palavra (s ou n)? ");
			scanf("%s",&op);
			if(op == 'n'){
				cont = 0;
				break;
			}else if(op == 's'){
				aviso = 0;
				break;
			}else printf("\nOpcao invalida\n");
		}
	}while(cont);
}

char *arquivo_rank(int nivel){
	char *filename;
	filename = malloc(sizeof(char)*6);
	switch (nivel) {
		case 1:
			strcpy(filename,"rank1");
			break;
		case 2:
			strcpy(filename,"rank2");
			break;
		case 3:
			strcpy(filename,"rank3");
			break;
		default:
			printf("Erro de ranking, nivel invalido\n");
			exit(1);
			break;
	}
	return filename;
}

void menu_add_rank(int nivel,int pontos){
	char *name;
	char *filename;
	struct Jogador *player;
	// player = malloc(sizeof(struct Jogador));
	// memset(player,0,sizeof(struct Jogador));
	filename = arquivo_rank(nivel);
	printf("Digite seu nome: ");
	name = ler_vetor(stdin);
	player = criar_jogador(name,pontos);
	// printf("your name = %s\nyour points = %d\n", player->nome,player->pontos);

	if( fwrite_jogador(player, filename,"ab") == EOF){
		printf("Erro ao adicionar jogador ao ranking\n");
		exit(1);
	}
	printf("Para ver sua posicao no rank acesse a opcao de ver o rank.\n");
	free(player);
}

void menu_show_rank(){
	int nivel = 0;
	char *filename;
	nivel = selecionar_nivel();
	filename = arquivo_rank(nivel);
	cleanit(0);

	if( !rankear(filename,nivel) ){
		printf("Nenhum jogador cadastrado no ranking desse nivel\n");
	}
	cleanit(1);
}

int rankear(char *filename,int nivel){
	struct Jogador **arr;
	FILE *arq;
	int i = 0;
	arq = fopen(filename,"rb");
	if(!arq){
		return 0;
		// printf("Nenhum jogador cadastrado no ranking desse nivel\n");
		// printf("Erro ao abrir arquivo ranking\n");
		// exit(1);
	}
	arr = fread_rank(arq);
	sort_rank(arr);
	printf("RANKING NIVEL %d:\n # Pontos  Nome\n",nivel);
	for(; i < NUM_J-1; i++){
		printf("%2d- %4d  %s\n",i+1,arr[i]->pontos,arr[i]->nome);
		free(arr[i]);
	}
	// arr = realloc(arr,sizeof(struct Jogador *));
	// free(arr);
	// printf("Aperte qualquer tecla para voltar\n");
	// getchar();
	// getchar();
	fclose(arq);
	return 1;
}
