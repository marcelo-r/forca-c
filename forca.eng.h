#ifndef FORCAENGINE_H_
#define FORCAENGINE_H_

#include "jogador.h"

/*Quantidade de jogadores carregados em um array de ranking*/
int NUM_J;

/*Tranforma todas as letras de uma string em underscore/underline (_)*/
void zera_palavra(char *to, char *from);

/*Procura em uma string a letra correspondente na forca e tranforma _ na letra*/
int acha_letra(char *palavra, char *forca, char letra);

/*Checa se uma letra eh valida para ser tentada na forca*/
char check_letra(char *letra);

/*Retorna o numero de letras de uma string, ignorando espaco e hífen*/
int str_len(char *word);

/*Classifica uma string com base no seu tamanho*/
int classificar_p(char *word);

/*Sorteia uma palavra, de um banco de struct Palavra, com o nivel desejado*/
char *palavra_aleatoria(FILE *arq,int nivel);

/*Escreve o ranking, 10 jogadores com maior pontuacao, em arquivo usando
  um array de ponteiros para structs Jogador*/
void fwrite_rank(FILE *,struct Jogador **);

/*Le por completo um arquivo contendo structs Jogador,
  retorna um array de ponteiros para as structs lidas*/
struct Jogador **fread_rank(FILE *);

/*Organiza o array contendo o ranking em ordem decrescente*/
void rsort_rank(struct Jogador **);

/*Adiciona uma nova struct Jogador ao array de ponteiros*/
struct Jogador **add_jogador(struct Jogador *player,struct Jogador **arr,int *size);

/*Executa as acoes necessarias para decidir de um jogador sera adicionado ao ranking*/
int rankear(char *filename,struct Jogador *player);

/*Decide qual o nome do arquivo basedo no nivel informado*/
char *arquivo_rank(int nivel);

#endif
