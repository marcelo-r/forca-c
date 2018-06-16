#ifndef FORCAENGINE_H_
#define FORCAENGINE_H_

#include "jogador.h"

void zera_palavra(char *to, char *from);
int acha_letra(char *palavra, char *forca, char letra);
char check_letra(char *letra);
int str_len(char *word);
int classificar_p(char *word);
char *palavra_aleatoria(FILE *arq,int nivel);

void fwrite_rank(FILE *,struct Jogador **);
struct Jogador **fread_rank(FILE *);
void rsort_rank(struct Jogador **);
struct Jogador **add_jogador(struct Jogador *player,struct Jogador **arr,int *size);

int rankear(char *filename,struct Jogador *player);
char *arquivo_rank(int nivel);

#endif
