#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogador.h"
#include "vetor.h"


struct Jogador *criar_jogador(char *nome,int points){
	struct Jogador *player;
	player = malloc(sizeof(*player) + ( sizeof(char) * (strlen(nome) + 1) ) );
	if(!player){
		printf("Erro de alocacao\n");
		exit(1);
	}
	player->pontos = points;
	strcpy(player->nome,nome);
	return player;
}

int fwrite_jogador(struct Jogador *player, char *filename,char *modo){
	FILE *arq;
	int len = 0;
	char c;
	arq = fopen(filename,modo);

	if(!arq){
		printf("Erro ao abrir arquivo ranking\n");
		exit(1);
	}

	if( fwrite(&(player->pontos), sizeof(int), 1, arq) != 1 ){
		printf("Erro ao escrever pontos\n");
		exit(1);
	}
	len = strlen(player->nome) + 1;
	if( fwrite(player->nome,sizeof(char),len,arq) != len){
		printf("Erro ao escrever nome do jogador\n");
		exit(1);
	}
	return fclose(arq);
}

struct Jogador *fread_jogador(FILE *arq){
	struct Jogador *player;
	char *name;
	if(!arq){
		printf("Erro arquivo rank\n");
		exit(1);
	}
	player = malloc(sizeof(struct Jogador));
	if( fread(&(player->pontos),sizeof(int),1,arq) != 1 ){
		free(player);
		return NULL;
	}
	name = ler_vetor(arq);
	player = realloc(player, sizeof(struct Jogador) + sizeof(char) * (strlen(name) + 1) );
	strcpy(player->nome,name);
	free(name);
	return player;
}

struct Jogador **fread_rank(FILE *arq){
	struct Jogador **arr;
	struct Jogador *player;
	int i = 0,len =0;
	arr = malloc(sizeof(struct Jogador *));
	if(!arq){
		printf("Erro arquivo fread_rank");
		exit(1);
	}
	while( (player = fread_jogador(arq)) != NULL){
		arr = realloc(arr,(sizeof(struct Jogador *) * i ) + sizeof(struct Jogador *));
		if(!arr){
			printf("Erro realloc fread_rank\n");
			exit(1);
		}
		len = strlen(player->nome) + 1;
		*(arr + i) = malloc(sizeof(struct Jogador) + len * sizeof(char));
		if(!(*(arr + i))){
			printf("Erro malloc fread_rank");
			exit(1);
		}
		(*(arr + i))->pontos = player->pontos;
		strcpy((*(arr + i))->nome,player->nome);
		i++;
		free(player);
	}
	free(player);
	NUM_J = i;
	return arr;
}

void sort_rank(struct Jogador **arr) {
	struct Jogador *aux;
	int len = NUM_J, i = 0, j = 0;
	for(i = 0; i < len; i++){
		for(j = 0; j < len-1; j++){
			if( arr[j]->pontos < arr[j+1]->pontos ){
				aux = arr[j+1];
				arr[j+1] = arr[j];
				arr[j] = aux;
			}
		}
	}
}
