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



char *recebe_vetor(char *str){
	unsigned int tamanho = 16, i = 0;
	int c = EOF;
	str = realloc(NULL,sizeof(char) * tamanho);
	if(!str){
		printf("\nErro de alocacao\n");
		return NULL;
	}
	getchar();
	while (( c = getchar() ) != '\n' && c != EOF){
		str[i++] = c;
		if(i == tamanho){
			tamanho += i;
			str = realloc(str,sizeof(char) * tamanho);
			if(!str) printf("Erro realloc");
		}
	}
	str[i] = '\0';
	return realloc(str,sizeof(char)*tamanho);
}

struct Palavra *criar_palavra(char *word,int nivel){
	struct Palavra sword = {nivel,*word};
	// sword = malloc( sizeof(*sword) + ( sizeof(char) * strlen(word) ) );
	//
	// if(!sword){
	// 	printf("Erro de alocacao");
	// 	exit(1);
	// }
	// sword->dificuldade = nivel;
	// strcpy(sword->palavra,word);
	return sword;
}
