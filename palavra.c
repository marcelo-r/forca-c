#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "palavra.h"
#include "vetor.h"

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

void zera_palavra(char *to, char *from){
	// if(strlen(from) != strlen(to)){
	// 	to = realloc(to, sizeof(char) * (strlen(from) + 1) );
	// 	if(!to){
	// 		printf("Erro realloc\n");
	// 		exit(1);
	// 	}
	// }
	for(; *from != '\0'; from++,to++){
		if(*from == ' ' || *from == '-') *to = *from;
		else *to = '_';
	}
	*(to++) = '\0';

}

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
