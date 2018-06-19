#ifndef JOGADOR_H_
#define JOGADOR_H_

struct Jogador{
	int pontos;
	char nome[];
};

/*Cria uma struct Jogador e retorna seu ponteiro*/
struct Jogador *criar_jogador(char *,int);

/*Le uma struct Jogador de um arquivo binario, retorna um ponteiro para a struct Jogador lida*/
struct Jogador *fread_jogador(FILE *);

/*Escreve uma struct Jogador num arquivo binario*/
void fwrite_jogador(FILE *,struct Jogador *);

#endif
