#ifndef FORCACLI_H_
#define FORCACLI_H_

/*Limpa a linha de comando*/
void cleanit(int aviso);

/*Menu principal*/
int menu();

/*Menu de jogar*/
int jogar();

/*Menu para selecionar o nivel*/
int selecionar_nivel();

/*Menu de cadastro de palavras na forca*/
void menu_cadastrar();

/*Menu de rankear uma partida para um jogador*/
void menu_rankear(int nivel,int pontos);

/*Menu de mostrar o ranking*/
void menu_rank();

/*Jogo da forca*/
int forca(char *word,char *empty);

/*Imprime o estado da forca*/
void imprime_forca(char *empty, int tamanho, int vidas,char *tentativas);

/*Recebe uma letra e é adiciona ou nao as letras ja tentadas*/
char recebe_letra(char *tentativas);

/*Imprime o ranking guardado em um arquivo*/
int list_rank(char *filename);

/*Creditos */
void creditos();

#endif
