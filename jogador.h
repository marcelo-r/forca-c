#ifndef JOGADOR_H_
#define JOGADOR_H_

int NUM_J;

struct Jogador{
	int pontos;
	char nome[];
};

struct Jogador *criar_jogador(char *,int);

struct Jogador *fread_jogador(FILE *);
void fwrite_jogador(FILE *,struct Jogador *);

#endif
