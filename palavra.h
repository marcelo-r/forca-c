#ifndef PALAVRA_H_
#define PALAVRA_H_

struct Palavra{
	int dificuldade;
	char palavra[];
};

void zera_palavra(char *to, char *from);
int acha_letra(char *palavra, char *forca, char letra);
char *ler_vetor(FILE *arq);

struct Palavra *criar_palavra(struct Palavra *sword, char *word,int nivel);

#endif
