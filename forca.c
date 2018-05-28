#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "palavra.h"

#define FILENAME "wordbank"

int menu();
void jogar();
int selecionar_nivel();
void menu_cadastrar();

void add_ao_banco(struct Palavra *sword, char *filename);
struct Palavra *fread_palavra(struct Palavra *sword,FILE *arq);
char *palavra_aleatoria(FILE *arq,int nivel);

int forca(char *word,char *empty);
void imprime_forca(char *empty, int tamanho, int vidas,char *tentativas);
char recebe_letra(char *tentativas);

int NUM_P;

int main() {
	srand( time(NULL) );
	NUM_P = 0;
 	for(;;){
  		if (menu() == 0) return 0;
		else return 1;
	}
}

int menu(){
	int opcao = 0;
	while(1){
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
				printf("\nTora Balde\n (aperte qualquer tecla para voltar)\n");
				getchar();
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
	FILE *arq;

	arq = fopen("wordbank","rb");
	if (!arq){
		printf("Erro ao abrir arquivo\n");
		exit(1);
	}
	do{
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

		raw_pontos = forca(word,empty) * nivel;
		printf("Voce fez %d pontos\n", raw_pontos);
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

char recebe_letra(char *tentativas){
	char letra, *t;
	int valida = 0;
	getchar();
	do {
		printf("Digite uma letra: ");
		scanf("%s", &letra);
		if( !((letra >= 65 && letra <= 90) || (letra >= 97 && letra <= 122)) ){
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
	int tamanho = strlen(word), vidas = 6, numtent = 0, erros = 0, fim = 0;
	char *tentativas;
	char letra;
	tentativas = malloc(sizeof(char) * 27);
	strcpy(tentativas,"");
	if(!tentativas){
		printf("Erro alocacao tentativas\n");
		exit(1);
	}
	do {
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
		if(vidas == 0){
			printf("\n--- YOU LOST ---\n");
			fim = 1;
		}
		if(strcmp(word,empty) == 0){
			printf("\n+++ YOU WIN +++\n");
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
		printf("\nSelecione a dificuldade:\n1 - Facil\n2 - Medio\n3 - Dificil\n > ");
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
		printf("\nDigite a palavra ou frase que deseja cadastrar na forca:\n> ");
		word = ler_vetor(stdin);
		// printf("Dificuldade: ");
		// scanf("%d", &nivel);
		nivel = selecionar_nivel();
		sword = criar_palavra(sword,word,nivel);
		add_ao_banco(sword,"wordbank");
		while(1){
			char op;
			printf("Cadastrar outra palavra (s ou n)? ");
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

// adiciona uma nova palavra ao banco
void add_ao_banco(struct Palavra *sword, char *filename){
	FILE *arq;
	int len = 0;
	int n = 0;
	arq = fopen(filename,"r+");
	if (!arq){
		arq = fopen(filename,"w");
	}
	fread(&n,sizeof(int),1,arq) != 1 ? n = 1 : n++;
	rewind(arq);
	if( fwrite(&n,sizeof(int),1,arq) != 1){
		printf("Erro ao escrever contador\n");
		exit(1);
	}
	if(fclose(arq) == EOF){
		printf("Erro ao fechar arquivo\n");
	}
	arq = fopen(filename,"ab");
	if (!arq){
		printf("Erro ao abrir arquivo em modo anexo\n");
		exit(1);
	}
	if( fwrite(&(sword->dificuldade), sizeof(int), 1, arq) != 1 ){
		printf("Erro ao escrever dificuldade em arquivo\n");
		exit(1);
	}
	len = strlen(sword->palavra)+1;
	if( fwrite(sword->palavra,sizeof(char), len, arq) != len ){
		printf("Erro ao escrever palavra em arquivo\n");
		exit(1);
	}
	fclose(arq);
}

struct Palavra *fread_palavra(struct Palavra *sword,FILE *arq){
	char *word;
	sword = malloc(sizeof(struct Palavra));
	if( fread(&(sword->dificuldade),sizeof(int),1,arq) != 1 ){
		printf("Erro ao ler dificuldade do arquivo\n");
		exit(1);
	}
	word = ler_vetor(arq);
	sword = realloc(sword,sizeof(sword) + sizeof(char) * (strlen(word) + 1) );
	strcpy(sword->palavra,word);
	free(word);
	return sword;
}

char *palavra_aleatoria(FILE *arq,int nivel){
	int qnt = 0, random = 0, i = 0, flag_nivel = 0,limite = 0;
	struct Palavra *sword;
	char *word;
	if (!arq){
		printf("Erro arquivo\n");
		exit(1);
	}
	rewind(arq);
	if( fread(&NUM_P,sizeof(int),1,arq) != 1){
		printf("Erro leitura NUM_P\n");
		exit(1);
	}
	/*
		rand() % (max_number + 1 - minimum_number) + minimum_number
				   NUM_P	 + 1 -		1		   +		1
	*/

	/*
	sorteia uma palavra, se ela nao possuir o nivel desejado,
	anda até achar uma que tenha o nível,
	se atingir EOF e nao achar, sorteia novamente
	*/
	do{
		rewind(arq);
		fseek(arq,sizeof(int),SEEK_SET);
		do{
			random = rand() % (NUM_P+1);
		}while(random == 0);
		// printf("\n++\nNUM_P = %d\nrandom = %d\n\n",NUM_P,random);
		for(i = 1; i <= random; i++){
			// printf("%d mizera\n",i);
			sword = fread_palavra(sword,arq);
		}
		if(sword->dificuldade == nivel){
			flag_nivel += 1;
			// break;
		}else{
			int j = NUM_P - random;
			for(i = 1; i <= j; i++){
				sword = fread_palavra(sword,arq);
				if(sword->dificuldade == nivel){
					flag_nivel += 1;
					break;
				}
			}
		}
		if (++limite > 10){
			free(sword);
			return NULL;
		}
	}while(flag_nivel == 0);

	word = malloc( sizeof(char) * (strlen(sword->palavra) + 1));
	strcpy(word,sword->palavra);

	return word;
}
