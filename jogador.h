#ifndef JOGADOR_H_
#define JOGADOR_H_

struct Jogador{
	int pontos;
	char nome[];
};

struct Jogador *criar_jogador(struct Jogador *player,char *nome,int pontos);

struct Jogador *fread_jogador(struct Jogador *player,FILE *arq);
int fwrite_jogador(struct Jogador *player, char *filename,char *modo);

int fwrite_rank(struct Jogador atual, int nivel);
struct Jogador **fread_rank(char *filename);

struct Jogador **sort_rank(struct Jogador **arr);
struct Jogador **add_jogador(struct Jogador *player,struct Jogador **arr);
#endif
