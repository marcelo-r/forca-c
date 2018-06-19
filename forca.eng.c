#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "forca.eng.h"
#include "vetor.h"
#include "palavra.h"
#include "jogador.h"

void zera_palavra(char *to, char *from){
	for(; *from != '\0'; from++,to++){
		if(*from == ' ' || *from == '-') *to = *from;
		else *to = '_';
	}
	*(to++) = '\0';
}

int acha_letra(char *palavra, char *forca, char letra){
	int sim = 0;
	for(; *palavra != '\0';palavra++,forca++){
		if(*palavra == letra){
			*forca = letra;
			sim = 1;
		}
	}
	return sim;
}

char check_letra(char *letra){
	if(!letra) return '\0';
	if( !((*letra >= 65 && *letra <= 90) || (*letra >= 97 && *letra <= 122) ) ) return '\0';
	return *letra;
}

int str_len(char *word){
	int len = 0;
	if(!word) return 0;
	for(; *word != '\0'; word++) if(*word != ' ') len++;
	return len;
}

int classificar_p(char *word){
	int len = 0;
	len = strlen(word);
	if (len <= 0) return 0;
	else if(len <= 6) return 1;
	else if(len <= 12) return 2;
	else return 3;
}

char *palavra_aleatoria(FILE *arq,int nivel){
	int qnt = 0, random = 0, i = 0, flag_nivel = 0,limite = 0,NUM_P = 0;
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
		for(i = 1; i <= random; i++){
			sword = fread_palavra(arq);
			if(i < random){
				free(sword);
			}
		}
		if(sword->dificuldade == nivel){
			flag_nivel += 1;
			break;
		}else{
			free(sword);
			int j = NUM_P - random;
			for(i = 1; i <= j; i++){
				sword = fread_palavra(arq);
				if(sword->dificuldade == nivel){
					flag_nivel += 1;
					break;
				}
				free(sword);
			}
		}
		if (++limite > 10){
			return NULL;
		}
	}while(flag_nivel == 0);

	word = malloc( sizeof(char) * (strlen(sword->palavra) + 1));
	strcpy(word,sword->palavra);
	free(sword);
	return word;
}

void fwrite_rank(FILE *arq,struct Jogador **arr){
	int i = 0;
	for(; i < NUM_J; i++){
		if(i < 10){
			fwrite_jogador(arq, arr[i]);
		}
		free(arr[i]);
	}
}

struct Jogador **fread_rank(FILE *arq){
	struct Jogador **arr;
	struct Jogador *player;
	int size = 0,len =0;
	arr = malloc(sizeof(struct Jogador *));
	if(!arq){
		return arr;
	}
	while( (player = fread_jogador(arq)) != NULL){
		arr = add_jogador(player,arr,&size);
		free(player);
	}
	free(player);
	NUM_J = size;
	return arr;
}

struct Jogador **add_jogador(struct Jogador *player,struct Jogador **arr,int *size){
	int len = 0, i = *size;
	arr = realloc(arr, (sizeof(struct Jogador *) * i) + sizeof(struct Jogador *) );
	if(!arr){
		printf("Erro realloc add_jogador\n");
		exit(1);
	}
	len = strlen(player->nome) + 1;
	*(arr + i) = malloc(sizeof(struct Jogador) + len * sizeof(char));
	if(!(*(arr + i))){
		printf("Erro malloc *arr[size] add_jogador");
		exit(1);
	}
	(*(arr + i))->pontos = player->pontos;
	strcpy((*(arr + i))->nome,player->nome);
	(*size)++;
	return arr;
}

void rsort_rank(struct Jogador **arr) {
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

char *arquivo_rank(int nivel){
	char *filename;
	filename = malloc(sizeof(char)*6);
	strcpy(filename,"rank");
	sprintf(filename,"rank%d",nivel);
	return filename;
}

int rankear(char *filename,struct Jogador *player){
	FILE *arq;
	struct Jogador **arr;
	int i = 0;
	arq = fopen(filename,"rb");
	if(!arq){
		arr = malloc(sizeof(struct Jogador *));
	}else{
		arr = fread_rank(arq);
		/* Ja tendo 10 e o player possuindo menos pontos que o ultimo,
		  nao eh preciso fazer nada */
		if(NUM_J >= 10 && player->pontos <= arr[NUM_J-1]->pontos){
			return fclose(arq);;
		}
		fclose(arq);
	}
	arr = add_jogador(player,arr,&NUM_J);
	if(NUM_J > 1) rsort_rank(arr);
	arq = fopen(filename,"wb");

	fwrite_rank(arq,arr);

	free(arr);
	return fclose(arq);
}
