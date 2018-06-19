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

void fwrite_jogador(FILE *arq,struct Jogador *player){
	int len = 0;
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
}

struct Jogador *fread_jogador(FILE *arq){
	struct Jogador *player;
	char *name;
	int points = 0;
	if(!arq){
		printf("Erro arquivo jogador\n");
		exit(1);
	}
	if( fread(&points,sizeof(int),1,arq) != 1 ){
		return NULL;
	}
	name = ler_vetor(arq);
	player = malloc(sizeof(struct Jogador) + sizeof(char) * (strlen(name) + 1) );
	player->pontos = points;
	strcpy(player->nome,name);
	free(name);
	return player;
}
