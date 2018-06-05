#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogador.h"
#include "vetor.h"


struct Jogador *criar_jogador(struct Jogador *player,char *nome,int points){
	player = malloc(sizeof(*player) + ( sizeof(char) * (strlen(nome) + 1) ) );
	// sword = malloc( sizeof(*sword) + ( sizeof(char) * (strlen(word) + 1) ) );
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
	// arq = fopen(filename,"rb");
	// if(!arq){
	// 	arq = fopen(filename,"wb");
	// 	rewind(arq);
	// }
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
	// fclose(arq);
	// arq = fopen(filename,"rb");
	// c = fgetc(arq);
	// while (c != EOF)
    // {
    //     printf ("%c", c);
    //     c = fgetc(arq);
    // }
	// printf("\n");
	return fclose(arq);
}

struct Jogador *fread_jogador(struct Jogador *player,FILE *arq){
	char *name;
	if(!arq){
		printf("Erro arquivo rank\n");
		exit(1);
	}
	player = malloc(sizeof(struct Jogador));
	if( fread(&(player->pontos),sizeof(int),1,arq) != 1 ){
		printf("Erro ao ler os pontos\n");
		return NULL;
		// exit(1);
	}
	name = ler_vetor(arq);
	player = realloc(player, sizeof(player) + sizeof(char) * (strlen(name) + 1) );
	strcpy(player->nome,name);
	free(name);
	return player;
}

struct Jogador **fread_rank(char *filename){
	struct Jogador **arr;
	struct Jogador *player;
	int i = 0;
	FILE *arq;
	arq = fopen(filename,"rb");
	if(!arq){
		printf("Erro ao abrir arquivo %s",filename);
		exit(1);
	}
	while( (player = fread_jogador(player,arq)) != NULL){
		printf("------------------------\n");
		printf("nome = %s\npontos = %d\n",player->nome,player->pontos );
		// player = fread_jogador(player,arq);
		arr = realloc(arr,sizeof(arr) + sizeof(struct Jogador *));
		if(!arr){
			printf("Erro realloc fread_rank\n");
			exit(1);
		}
		*(arr + i) = malloc(sizeof(player));
		if(!(*(arr + i))){
			printf("Erro malloc fread_rank");
			exit(1);
		}
		(*(arr + i))->pontos = player->pontos;
		strcpy((*(arr + i))->nome,player->nome);
		i++;
		free(player);
	}
	printf("SAIU\n");
	arr = realloc(arr,sizeof(arr) + sizeof(struct Jogador *));
	(*(arr + i + 1))->pontos = 0;
	strcpy((*(arr + i + 1))->nome,"");
	free(player);
	return arr;
}

struct Jogador **sort_rank(struct Jogador **arr) {
	struct Jogador *aux,**copy;
	int len = 0,i = 0, j = 0;
	copy = arr;
	for(; (*copy)->pontos != 0; copy++,len++);
	for(i = 0; i < len; i++){
		for(j = 0; j < len-i; j++){
			if( (arr[j])->pontos < (arr[j+1])->pontos ){
				aux = arr[j+1];
				arr[j+1] = arr[j];
				arr[j] = aux;
			}
		}
	}
	return arr;
}

struct Jogador **add_jogador(struct Jogador *player,struct Jogador **arr){
	struct Jogador **cpy = arr;
	int len = 0;
	// cpy = arr;
	for(; (*cpy)->pontos != 0;cpy++){
		if( strcmp((*cpy)->nome,player->nome) ){
			(*cpy)->pontos = player->pontos;
			return arr;
		}
		len++;
	}
	len++;
	arr = realloc(arr,sizeof(arr) + sizeof(struct Jogador *));
	*(arr + len + 1) = malloc(sizeof(player));
	(*(arr + len + 1))->pontos = player->pontos;
	strcpy((*(arr + len + 1))->nome,player->nome);
	return arr;
}
