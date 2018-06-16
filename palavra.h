#ifndef PALAVRA_H_
#define PALAVRA_H_

int NUM_P;

struct Palavra{
	int dificuldade;
	char palavra[];
};

void zera_palavra(char *to, char *from);
int acha_letra(char *palavra, char *forca, char letra);
char check_letra(char *letra);
int str_len(char *word);

struct Palavra *criar_palavra(struct Palavra *sword, char *word,int nivel);

int fwrite_palavra(struct Palavra *sword, char *filename);
struct Palavra *fread_palavra(FILE *arq);
char *palavra_aleatoria(FILE *arq,int nivel);

#endif
