#ifndef PALAVRA_H_
#define PALAVRA_H_

struct Palavra{
	int dificuldade;
	char palavra[];
};

struct Palavra *criar_palavra(struct Palavra *sword, char *word,int nivel);

int fwrite_palavra(struct Palavra *sword, char *filename);
struct Palavra *fread_palavra(FILE *arq);

#endif
