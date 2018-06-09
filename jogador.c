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

struct Jogador *fread_jogador(FILE *arq){
	struct Jogador *player;
	char *name;
	if(!arq){
		printf("Erro arquivo rank\n");
		exit(1);
	}
	player = malloc(sizeof(struct Jogador));
	// algumas vezes, ao tentar ver o ranking, ocorre um erro aqui no fread
	if( fread(&(player->pontos),sizeof(int),1,arq) != 1 ){
		return NULL;
		// exit(1);
	}
	name = ler_vetor(arq);
	player = realloc(player, sizeof(player) + sizeof(char) * (strlen(name) + 1) );
	strcpy(player->nome,name);
	free(name);
	return player;
}

struct Jogador **fread_rank(FILE *arq){
	struct Jogador **arr;
	struct Jogador *player;
	int i = 0;
	// FILE *arq;
	// arq = fopen(filename,"rb");
	arr = malloc(sizeof(struct Jogador *));
	if(!arq){
		printf("Erro arquivo fread_rank");
		exit(1);
	}
	while( (player = fread_jogador(arq)) != NULL){
		// player = fread_jogador(player,arq);
		// printf("\n\n?????????????????\n\n");
		arr = realloc(arr,(sizeof(struct Jogador *) * i ) + sizeof(struct Jogador *));
		if(!arr){
			printf("Erro realloc fread_rank\n");
			exit(1);
		}
		*(arr + i) = malloc(sizeof(struct Jogador *));
		if(!(*(arr + i))){
			printf("Erro malloc fread_rank");
			exit(1);
		}
		(*(arr + i))->pontos = player->pontos;
		strcpy((*(arr + i))->nome,player->nome);
		// printf("------------------------\n");
		// printf("nome = %s\npontos = %d\n",(*(arr + i))->nome,(*(arr + i))->pontos );
		i++;
		free(player);
	}
	// printf("SAIU %d\n",i);
	i++;
	arr = realloc(arr,sizeof(struct Jogador *) * i );
	*(arr + i) = malloc(sizeof(struct Jogador));
	(*(arr + i))->pontos = 0;
	strcpy((*(arr + i))->nome," ");
	free(player);
	// fclose(arq);
	NUM_J = i;
	return arr;
}

void sort_rank(struct Jogador **arr) {
	struct Jogador *aux;
	int len = NUM_J-1, i = 0, j = 0;
	for(i = 0; i < len; i++){
		// printf("i-%d\n",i);
		for(j = 0; j < len-1; j++){
			// printf("j-%d ",j);
			if( arr[j]->pontos < arr[j+1]->pontos ){
				// printf("+++ \n");
				aux = arr[j+1];
				arr[j+1] = arr[j];
				arr[j] = aux;
			}
		}
	}
}
