#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "palavra.h"

#define FILENAME "wordbank"

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

int forca(char *word,char *empty);
void imprime_forca(char *empty, int tamanho, int vidas,char *tentativas);
char recebe_letra(char *tentativas);

char check_letra(char *letra);
int str_len(char *word);

void cleanit();


int main() {
	printf("%c\n",os);
	srand( time(NULL) );
	NUM_P = 0;
 	for(;;){
  		if (menu() == 0) return 0;
		else return 1;
	}
}

void cleanit(){
	if(os == 'l') system("clear && clear");
	else system("cls");
}

int menu(){
	int opcao = 0;
	while(1){
		cleanit();
		printf("1 - Jogar\n2 - Ver Ranking\n3 - Cadastrar Palavras\n4 - Creditos\n5 - Sair\n > ");
		scanf("%d",&opcao);
		switch (opcao) {
			case 1:
				jogar();
				break;
			case 2:
				// ranking();
				printf("\nEm breve\n");
				break;
			case 3:
				menu_cadastrar();
				break;
			case 4:
				// creditos();
				printf("\nBy Tora Balde\n\n");
				break;
			case 5:
				printf("\n!\n");
				return 0;
			default:
				printf("\nOpcao invalida\n");
		}
	}
	return 1;
}

void jogar(){
	int nivel,tamanho,cont_j = 1, raw_pontos = 0;
	char *word,*empty;
	char deseja = ' ';
	time_t start,end;
	double tempo = 0.0, pontos = 0.0;
	FILE *arq;

	arq = fopen("wordbank","rb");
	if (!arq){
		printf("Erro ao abrir arquivo\n");
		exit(1);
	}
	do{
		cleanit();
		nivel = selecionar_nivel();
		word = palavra_aleatoria(arq,nivel);
		if(!word){
			printf("Nao existem palavras desse nivel\n");
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
		pontos = (raw_pontos / tempo) * 100.0;

		printf("A palavra era: %s\n", word);
		printf("Voce fez %.0f pontos\n", pontos);
		printf("Tempo gasto %.0f segundos\n", tempo);
		// pontuar();
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

	// free(word);
	// free(empty);
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
	int tamanho = str_len(word), vidas = 6, numtent = 0, erros = 0, fim = 0;
	char *tentativas;
	char letra;
	tentativas = malloc(sizeof(char) * 27);
	strcpy(tentativas,"");
	if(!tentativas){
		printf("Erro alocacao tentativas\n");
		exit(1);
	}
	do {
		cleanit();
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
		}
		// if(vidas == 0){
		// 	printf("\n--- YOU LOST ---\n");
		// 	fim = 1;
		// }
		if(strcmp(word,empty) == 0 || vidas == 0){
			imprime_forca(empty,tamanho,vidas,tentativas);
			fim = 1;
		}
	} while(!fim);

	return (vidas * (numtent - erros));
}

void imprime_forca(char *empty, int tamanho, int vidas,char *tentativas){
	// char boneco[12] = "";
	printf("\n===========\nA palavra possui %d letras\n",tamanho);
	printf("\n>  %s  <\n",empty);
	printf("\nVidas: %d\n", vidas);
	printf("Tentadas: %s\n", tentativas);
	// printf("__\n  |\n");
	// switch (vidas) {
	// 	case 5:
	// 		strcat(boneco,"  o");
	// 		// printf("o\n");
	// 	case 4:
	// 		strcat(boneco,"")
	// 		// printf("o\n-\n");
	// 	case 3:
	// 		// printf(" -");
	// 	case 2:
	// 		// printf("\n |");
	// 	case 1:
	// 		// printf("\n/");
	// 	case 0:
	// 		// printf(" \\");
	// 		break;
	// 	default:
	// 		// printf("\n");
	// }
}

int selecionar_nivel(){
	int nivel = 0;
	do{
		printf("Selecione a dificuldade:\n1 - Facil\n2 - Medio\n3 - Dificil\n > ");
		scanf("%d",&nivel);
		if(nivel != 1 && nivel != 2 && nivel != 3){
			printf("Opcao invalida");
			nivel = 0;
		}
	}while(nivel == 0);
	return nivel;
}

void menu_cadastrar(){
	char *word;
	int nivel = 0, cont = 1;
	struct Palavra *sword;
	do{
		cleanit();
		printf("Digite a palavra ou frase que deseja cadastrar na forca:\n> ");
		word = ler_vetor(stdin);
		// printf("Dificuldade: ");
		// scanf("%d", &nivel);
		nivel = selecionar_nivel();
		sword = criar_palavra(sword,word,nivel);
		if(!fwrite_palavra(sword,"wordbank")){
			printf("Erro ao cadastrar, tente novamente.\n");
			continue;
		}
		printf("Palavra cadastrada com sucesso.\n");
		while(1){
			char op;
			printf("\nCadastrar outra palavra (s ou n)? ");
			scanf("%s",&op);
			if(op == 'n'){
				cont = 0;
				break;
			}else if(op == 's'){
				break;
			}else printf("\nOpcao invalida\n");
		}
	}while(cont);
}

int str_len(char *word){
	int len = 0;
	if(!word) return 0;
	for(; *word != '\0'; word++) if(*word != ' ') len++;
	return len;
}
