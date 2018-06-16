#ifndef JOGADOR_H_
#define JOGADOR_H_

int NUM_J;

struct Jogador{
	int pontos;
	char nome[];
};

struct Jogador *criar_jogador(char *,int);

struct Jogador *fread_jogador(FILE *);
int fwrite_jogador(struct Jogador *, char *,char *);

int fwrite_rank(struct Jogador, int);
struct Jogador **fread_rank(FILE *);

void sort_rank(struct Jogador **);

#endif
