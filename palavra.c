#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "palavra.h"

void acha_letra(char *palavra, char *forca, char letra){
  for(; *palavra != '\0';palavra++,forca++){
    if(*palavra == letra) *forca = letra;
  }
}

void zera_palavra(char *from, char *to){
	for(; *from != '\0'; from++,to++){
		if(*from == ' ' || *from == '-') *to = *from;
		else *to = '_';
	}
	*(to++) = '\0';
}

char *ler_vetor(FILE *arq){
	char *str;
	unsigned int tamanho = 16, i = 0;
	int c;
	str = realloc(NULL,sizeof(char) * tamanho);
	if(!str){
		printf("\nErro de alocacao\n");
		return NULL;
	}
	if(arq == stdin) getchar();
	while (( c = fgetc(arq) ) != EOF && c != '\n' && c != '\0'){
		str[i++] = c;
		if(i == tamanho){
			tamanho += i;
			str = realloc(str,sizeof(char) * tamanho);
			if(!str) printf("Erro realloc\n");
		}
	}
	str[i] = '\0';
	return realloc( str, sizeof(char)*(strlen(str)+1) );
}

struct Palavra *criar_palavra(struct Palavra *sword, char *word,int nivel){
	sword = malloc( sizeof(*sword) + ( sizeof(char) * strlen(word) ) );
	if(!sword){
		printf("Erro de alocacao\n");
		exit(1);
	}
	sword->dificuldade = nivel;
	strcpy(sword->palavra,word);
	return sword;
}
