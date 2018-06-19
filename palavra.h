#ifndef PALAVRA_H_
#define PALAVRA_H_

struct Palavra{
	int dificuldade;
	char palavra[];
};

/*Cria e retorna um ponteiro para a struct Palavra criada com nivel e word */
struct Palavra *criar_palavra(struct Palavra *sword, char *word,int nivel);

/*Escreve uma struct Palavra no arquivo com nome filename*/
int fwrite_palavra(struct Palavra *sword, char *filename);

/*Le de um stream de um arquivo binario os bytes correspondentes a uma struct Palavra*/
struct Palavra *fread_palavra(FILE *arq);

#endif
