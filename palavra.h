#ifndef PALAVRA_H_
#define PALAVRA_H_

struct Palavra{
	int dificuldade;
	char palavra[];
};

void zera_palavra(char *from, char *to);
void acha_letra(char *palavra, char *forca, char letra);
char *recebe_vetor(char *str);

struct Palavra *criar_palavra(struct Palavra *sword, char *word,int nivel);

#endif
