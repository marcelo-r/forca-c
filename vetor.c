#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vetor.h"

char *ler_vetor(FILE *arq){
	char *str;
	unsigned int tamanho = 8, i = 0;
	int c;
	str = malloc(sizeof(char) * tamanho);
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
