#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "palavra.h"
#include "vetor.h"

struct Palavra *criar_palavra(struct Palavra *sword, char *word,int nivel){
	sword = malloc( sizeof(*sword) + ( sizeof(char) * (strlen(word) + 1) ) );
	if(!sword){
		printf("Erro de alocacao\n");
		exit(1);
	}
	sword->dificuldade = nivel;
	strcpy(sword->palavra,word);
	return sword;
}

int fwrite_palavra(struct Palavra *sword, char *filename){
	FILE *arq;
	int len = 0;
	int n = 0;
	arq = fopen(filename,"rb+");
	if (!arq){
		arq = fopen(filename,"wb");
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
		printf("Erro ao abrir arquivo em modo append\n");
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
	return fclose(arq);
}

struct Palavra *fread_palavra(FILE *arq){
	struct Palavra *sword;
	char *word;
	sword = malloc(sizeof(struct Palavra));
	if( fread(&(sword->dificuldade),sizeof(int),1,arq) != 1 ){
		printf("Erro ao ler dificuldade do arquivo\n");
		exit(1);
	}
	word = ler_vetor(arq);
	sword = realloc(sword,sizeof(struct Palavra) + sizeof(char) * (strlen(word) + 1) );
	strcpy(sword->palavra,word);
	free(word);
	return sword;
}
