#ifndef JOGADOR_H_
#define JOGADOR_H_

int NUM_J;

struct Jogador{
	int pontos;
	char nome[];
};

struct Jogador *criar_jogador(char *nome,int pontos);

struct Jogador *fread_jogador(FILE *arq);
int fwrite_jogador(struct Jogador *player, char *filename,char *modo);

int fwrite_rank(struct Jogador atual, int nivel);
struct Jogador **fread_rank(FILE *arq);

void sort_rank(struct Jogador **arr);

#endif
