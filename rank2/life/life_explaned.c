/* ************************************************************************** */
/*  LIFE - Jogo da Vida de Conway (exame 42)                                  */
/*                                                                            */
/*  Uso: ./life width height iterations < comandos                            */
/*                                                                            */
/*  Fluxo geral do programa:                                                  */
/*    1. init_game   -> le os argumentos e cria o tabuleiro vazio             */
/*    2. fill_board  -> le o stdin (w a s d x) e "desenha" as celulas vivas   */
/*    3. play        -> executa UMA geracao (chamada 'iterations' vezes)      */
/*    4. print_board -> imprime o resultado                                   */
/*    5. free_board  -> libera a memoria                                      */
/* ************************************************************************** */

#include "life.h"

/*
** init_game
** Preenche a struct com os parametros e aloca o tabuleiro (matriz 2D).
** Retorna 0 em sucesso e -1 se algum malloc/calloc falhar.
*/
int init_game(t_game* game, char* argv[])
{
	/* atoi converte string -> int (argv[0] e o nome do programa) */
	game->width = atoi(argv[1]);
	game->height = atoi(argv[2]);
	game->iterations = atoi(argv[3]);

	game->alive = 'O';   /* caractere que representa celula viva  */
	game->dead = ' ';    /* caractere que representa celula morta */

	/* posicao da "caneta": comeca no canto superior esquerdo (0,0) */
	game->i = 0;         /* linha  (eixo vertical)   */
	game->j = 0;         /* coluna (eixo horizontal) */
	game->draw = 0;      /* 0 = caneta levantada, 1 = caneta abaixada */

	/*
	** Aloca o vetor de linhas (um ponteiro por linha).
	** CORREÇÃO: usei calloc em vez de malloc para que todos os ponteiros
	** comecem como NULL. No original, se o malloc de uma linha falhasse,
	** free_board() chamava free() em ponteiros nao inicializados (lixo)
	** nas linhas seguintes -> comportamento indefinido.
	*/
	game->board = (char**)calloc(game->height, sizeof(char *));
	if(!(game->board))
		return(-1);

	/* Aloca cada linha (width caracteres) e preenche com celulas mortas */
	for(int i = 0; i < game->height; i++)
	{
		game->board[i] = (char *)malloc((game->width) * sizeof(char));
		if(!(game->board[i])) {
			free_board(game);   /* libera o que ja foi alocado (o resto e NULL) */
			return(-1);
		}
		for(int j = 0; j < game->width; j++)
		{
			game->board[i][j] = ' ';
		}
	}
	return(0);
}

/*
** fill_board
** Le o stdin caractere a caractere ate o EOF e executa os comandos:
**   w = cima | s = baixo | a = esquerda | d = direita | x = liga/desliga caneta
** Se a caneta estiver abaixada, a celula onde ela esta fica viva.
*/
void fill_board(t_game* game)
{
	char buffer;
	int flag;

	/* read devolve 1 enquanto conseguir ler um byte; 0 no EOF */
	while(read(STDIN_FILENO, &buffer, 1) == 1)
	{
		/*
		** CORREÇÃO: flag agora e zerada a CADA caractere.
		** No original ela era declarada fora do while e nunca voltava a 0:
		** bastava um caractere invalido (ex.: '\n' do echo no meio da entrada)
		** para a caneta parar de desenhar para sempre.
		*/
		flag = 0;

		switch (buffer)
		{
		case 'w':                        /* sobe: linha diminui */
			if(game->i > 0)              /* nao deixa sair pelo topo */
				game->i--;
			break;
		case 's':                        /* desce: linha aumenta */
			if(game->i < (game->height - 1))   /* nao sai por baixo */
				game->i++;
			break;
		case 'a':                        /* esquerda: coluna diminui */
			if(game->j > 0)
				game->j--;
			break;
		case 'd':                        /* direita: coluna aumenta */
			if(game->j < (game->width - 1))
				game->j++;
			break;
		case 'x':                        /* inverte o estado da caneta */
			game->draw = !(game->draw);
			break;
		default:                         /* qualquer outro caractere e ignorado */
			flag = 1;
			break;
		}

		/*
		** Depois de cada comando valido, se a caneta esta abaixada,
		** marca a posicao atual como viva. Isso tambem faz com que o 'x'
		** que ABAIXA a caneta ja desenhe a celula onde ela esta (o exemplo
		** do enunciado exige isso).
		*/
		if(game->draw && (flag == 0))
		{
			/* checagem de seguranca (os limites ja sao garantidos acima) */
			if((game->i >= 0 )&& (game->i < game->height) && (game->j >= 0) && (game->j < game->width))
				game->board[game->i][game->j] = game->alive;
		}
	}
}

/*
** count_neighbors
** Conta quantos dos 8 vizinhos da celula (i, j) estao vivos.
** Celulas fora do tabuleiro sao consideradas mortas (regra do enunciado),
** por isso basta ignora-las.
*/
int count_neighbors(t_game* game, int i, int j)
{
	int count = 0;

	/* di e dj variam em {-1, 0, 1}: percorre o quadrado 3x3 ao redor */
	for(int di = -1; di < 2; di++)
	{
		for(int dj = -1; dj < 2; dj++)
		{
			/* (0,0) e a propria celula, nao e vizinha de si mesma */
			if((di == 0) && (dj == 0))
				continue;

			int ni = i + di;   /* linha do vizinho  */
			int nj = j + dj;   /* coluna do vizinho */

			/* so conta se o vizinho estiver DENTRO do tabuleiro */
			if((ni >= 0) && (nj >=0) && (ni < game->height) && (nj < game->width)) {
				if(game->board[ni][nj] == game->alive)
					count++;
			}
		}
	}
	return(count);
}

/*
** play
** Calcula UMA geracao. Importante: a nova geracao e escrita num tabuleiro
** temporario (temp), porque se alterassemos o tabuleiro original enquanto
** o percorremos, as celulas ja atualizadas contaminariam a contagem de
** vizinhos das proximas.
**
** Regras de Conway:
**   - Celula viva  com 2 ou 3 vizinhos vivos -> continua viva
**   - Celula viva  com qualquer outro numero  -> morre
**   - Celula morta com exatamente 3 vizinhos  -> nasce
**   - Celula morta com qualquer outro numero  -> continua morta
*/
int play(t_game* game)
{
	/* Aloca o tabuleiro temporario (calloc: ponteiros iniciam em NULL) */
	char** temp = (char**)calloc(game->height, sizeof(char *));
	if(!temp)
		return(-1);

	for(int i = 0; i < game->height; i++)
	{
		temp[i] = (char *)malloc((game->width) * sizeof(char));
		if(!(temp[i]))
		{
			/*
			** CORREÇÃO: o original retornava -1 sem liberar o que ja tinha
			** sido alocado em temp (vazamento de memoria). Aqui liberamos.
			*/
			for(int k = 0; k < i; k++)
				free(temp[k]);
			free(temp);
			return(-1);
		}
	}

	/* Calcula o novo estado de cada celula a partir do tabuleiro ATUAL */
	for(int i = 0; i < game->height; i++)
	{
		for(int j = 0; j < game->width; j++)
		{
			int neighbors = count_neighbors(game, i, j);

			if(game->board[i][j] == game->alive) {
				/* viva: sobrevive com 2 ou 3 vizinhos */
				if(neighbors == 2 || neighbors == 3) {
					temp[i][j] = game->alive;
				}
				else
					temp[i][j] = game->dead;   /* solidao ou superpopulacao */
			}
			else {
				/* morta: nasce com exatamente 3 vizinhos */
				if(neighbors == 3) {
					temp[i][j] = game->alive;
				}
				else
					temp[i][j] = game->dead;
			}
		}
	}

	/* Libera o tabuleiro antigo e passa a usar o novo */
	free_board(game);
	game->board = temp;
	return(0);
}

/*
** print_board
** Imprime o tabuleiro linha a linha. Usa apenas putchar (unica funcao de
** saida permitida no exame). Cada linha termina com '\n'.
*/
void print_board(t_game* game)
{
	for(int i = 0; i < game->height; i++)
	{
		for(int j = 0; j < game->width; j++)
		{
			putchar(game->board[i][j]);
		}
		putchar('\n');
	}
}

/*
** free_board
** Libera cada linha e depois o vetor de ponteiros.
** Os testes "if" evitam free() em ponteiros NULL (caso de falha parcial
** na alocacao).
*/
void free_board(t_game* game)
{
	if(game->board)
	{
		for(int i = 0; i < game->height; i++)
		{
			if(game->board[i])
				free(game->board[i]);
		}
		free(game->board);
	}
}

/*
** main
** Valida os argumentos e orquestra as etapas do programa.
*/
int main(int argc, char* argv[])
{
	/* precisa de exatamente 3 argumentos: width height iterations */
	if(argc != 4)
		return (1);

	t_game game;

	/* 1. cria o tabuleiro vazio */
	if(init_game(&game, argv) == -1)
		return(1);

	/* 2. le o stdin e desenha a configuracao inicial */
	fill_board(&game);

	/* 3. simula as geracoes pedidas (com 0 iteracoes, so imprime o desenho) */
	for(int i = 0; i < game.iterations; i++) {
		if(play(&game) == -1) {
			free_board(&game);
			return(1);
		}
	}

	/* 4. imprime o resultado e 5. libera a memoria */
	print_board(&game);
	free_board(&game);

	return (0);
}
