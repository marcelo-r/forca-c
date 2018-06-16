#ifndef FORCACLI_H_
#define FORCACLI_H_

int menu();
void jogar();
int selecionar_nivel();
void menu_cadastrar();
void menu_add_rank(int nivel,int pontos);
void menu_rank();
int forca(char *word,char *empty);
void imprime_forca(char *empty, int tamanho, int vidas,char *tentativas);
char recebe_letra(char *tentativas);
int list_rank(char *filename);
void cleanit(int aviso);

#endif
