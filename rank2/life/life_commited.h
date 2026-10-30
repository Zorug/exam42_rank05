
/*
** life.h - Cabecalho do programa "life"
**
** Contem: includes das bibliotecas, a struct que guarda TODO o estado do
** jogo e os prototipos das funcoes implementadas em life.c.
*/

/*
** Include guard: evita que este arquivo seja incluido duas vezes na mesma
** compilacao (o que daria erro de "redefinicao de t_game").
*/
#ifndef LIFE
#define LIFE

#include <stdlib.h>   /* malloc, free, atoi (e calloc/realloc, se precisar) */
#include <unistd.h>   /* read e STDIN_FILENO (descritor 0 = entrada padrao) */
#include <stdio.h>    /* putchar */


/*
** t_game: agrupa tudo o que o programa precisa num unico lugar, assim
** passamos so um ponteiro (t_game*) para as funcoes em vez de varias variaveis.
*/
typedef struct s_game
{
	int width;        /* largura do tabuleiro (numero de colunas) - argv[1] */
	int height;       /* altura do tabuleiro (numero de linhas)   - argv[2] */
	int iterations;   /* quantas geracoes simular                 - argv[3] */
	char alive;       /* caractere de celula viva: 'O'                      */
	char dead;        /* caractere de celula morta: ' ' (espaco)            */
	int i;            /* posicao da "caneta": linha atual                   */
	int j;            /* posicao da "caneta": coluna atual                  */
	int draw;         /* estado da caneta: 0 = levantada, 1 = abaixada      */
	char** board;     /* tabuleiro: matriz 2D de chars, acessada board[i][j]
	                     (i = linha, j = coluna)                            */
} t_game;

/* Prototipos (declaracoes) das funcoes definidas em life.c */
int init_game(t_game* game, char* argv[]);   /* prepara a struct e cria o tabuleiro */
void fill_board(t_game* game);               /* le o stdin e desenha o tabuleiro    */
int play(t_game* game);                      /* calcula UMA geracao                 */
void print_board(t_game* game);              /* imprime o tabuleiro                 */
void free_board(t_game* game);               /* libera a memoria do tabuleiro       */


#endif
