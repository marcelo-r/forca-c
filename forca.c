#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "palavra.h"

int menu();

void jogar();
int selecionar_nivel();
void menu_cadastrar();

void add_ao_banco(struct Palavra *sword, char *filename);
char *sortear_palavra(char *filename);

#define FILENAME "wordbank"
#define EASY "easy"
#define MEDIUM "medium"
#define HARD "hard"

int main() {
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
				printf("\nTora Balde\n");
				sortear_palavra(FILENAME);
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
	int *nivel;
	char *word,*empty;

	word = malloc(sizeof(char));

	selecionar_nivel(nivel);

	word = recebe_vetor(word);

	// sorteia_palavra();

	//word = (char *) malloc(20);
	empty = (char *) malloc(sizeof(word));
	//word = "marcelo rolim";
	zera_palavra(word,empty);
	printf("\n1-\n%s\n%s", word,empty);
	acha_letra(word,empty,'a');
	printf("\n%s\n%s\n", word,empty);

	free(word);
	free(empty);
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
	struct Palavra sword;
	do{
		printf("\nDigite a palavra ou frase que deseja cadastrar na forca:\n> ");
		word = recebe_vetor(word);
		printf("Dificuldade: ");
		scanf("%d", &nivel);
		sword = criar_palavra(word,nivel);
		add_ao_banco(&sword,FILENAME);
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

void add_ao_banco(struct Palavra *sword, char *filename){
	FILE *arq;
	arq = fopen(filename,"ab");
	if (!arq){
		printf("Erro ao abrir arquivo");
		exit(1);
	}
	if( fwrite(sword, sizeof(sword), 1, arq) != 1 ){
		printf("Erro ao escrever em arquivo\n");
		exit(1);
	}
	fclose(arq);
}

char *sortear_palavra(char *filename){
	FILE *arq;
	// int i;
	struct Palavra *p;
	arq = fopen(filename,"rb");
	if (!arq){
		printf("Erro ao abrir arquivo");
		exit(1);
	}

	for(size_t i = 0; i < 2; i++){
		fread(p,sizeof(struct Palavra),1,arq);
		printf("n = %s\n", p->palavra);
	}
}
