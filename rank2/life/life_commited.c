/*
** life.c - Jogo da Vida de Conway (exame 42)
**
** Uso: ./life width height iterations   (comandos lidos do stdin)
**
** Fluxo do programa (ver main no final do arquivo):
**   1. init_game   -> le os argumentos e cria o tabuleiro vazio
**   2. fill_board  -> le o stdin (w a s d x) e desenha as celulas vivas
**   3. play        -> calcula UMA geracao (chamada 'iterations' vezes)
**   4. print_board -> imprime o resultado
**   5. free_board  -> libera a memoria
*/

#include "life.h"

/*
** init_game
** Preenche a struct com os parametros e aloca o tabuleiro (matriz 2D).
** Retorna 0 se tudo correu bem, -1 se alguma alocacao falhou.
*/
int init_game(t_game* game, char* argv[])
{
	/* atoi converte texto -> numero. argv[0] e o nome do programa, por isso
	   os argumentos comecam em argv[1]. */
	game->width = atoi(argv[1]);
	game->height = atoi(argv[2]);
	game->iterations = atoi(argv[3]);

	game->alive = 'O';   /* como uma celula viva e impressa  */
	game->dead = ' ';    /* como uma celula morta e impressa */

	/* A caneta comeca no canto superior esquerdo (linha 0, coluna 0),
	   com a ponta levantada (draw = 0), ou seja, ainda nao desenha. */
	game->i = 0;
	game->j = 0;
	game->draw = 0;

	/* Passo 1 da matriz 2D: aloca um vetor com 'height' ponteiros,
	   um para cada linha. */
	game->board = (char**)malloc((game->height) * sizeof(char *));
	if(!(game->board))      /* malloc devolve NULL se nao houver memoria */
		return(-1);

	/* Passo 2: para cada linha, aloca 'width' caracteres. */
	for(int i = 0; i < game->height; i++)
	{
		game->board[i] = (char *)malloc((game->width) * sizeof(char));
		if(!(game->board[i])) {
			/* falhou: libera o que ja foi alocado e avisa o main */
			free_board(game);
			return(-1);
		}
		/* Passo 3: preenche a linha com espacos (todas as celulas mortas).
		   O malloc nao inicializa a memoria, por isso e preciso fazer isto. */
		for(int j = 0; j < game->width; j++)
		{
			game->board[i][j] = ' ';
		}
	}
	return(0);
}

/*
** fill_board
** Le o stdin um caractere de cada vez ate o fim da entrada (EOF) e executa
** cada comando:
**    w = sobe | s = desce | a = esquerda | d = direita
**    x = levanta/abaixa a caneta
** Com a caneta abaixada, a celula onde ela esta passa a ficar viva.
*/
void fill_board(t_game* game)
{
	char buffer;      /* guarda o caractere lido */
	int flag = 0;     /* 0 = comando valido | 1 = caractere desconhecido */

	/* read(fd, destino, quantidade) devolve quantos bytes leu:
	   1 = leu um caractere | 0 = fim da entrada (EOF) | -1 = erro.
	   O ciclo termina quando ja nao ha mais nada para ler. */
	while(read(STDIN_FILENO, &buffer, 1) == 1)
	{
		switch (buffer)
		{
		case 'w':                       /* cima: a linha diminui */
			if(game->i > 0)             /* so move se nao estiver no topo */
			game->i--;
			break;
		case 's':                       /* baixo: a linha aumenta */
			if(game->i < (game->height - 1))   /* so move se nao estiver na ultima linha */
			game->i++;
			break;
		case 'a':                       /* esquerda: a coluna diminui */
			if(game->j > 0)             /* so move se nao estiver na primeira coluna */
			game->j--;
			break;
		case 'd':                       /* direita: a coluna aumenta */
			if(game->j < (game->width - 1))    /* so move se nao estiver na ultima coluna */
			game->j++;
			break;
		case 'x':                       /* inverte o estado da caneta: 0 -> 1 ou 1 -> 0 */
			game->draw = !(game->draw);
			break;
		default:                        /* qualquer outro caractere (ex.: '\n') */
			flag = 1;                   /* marca como "nao e comando" */
			break;
		}

		/* Se a caneta esta abaixada e o caractere era um comando valido,
		   marca a posicao atual como viva. Como isto vem DEPOIS do switch,
		   o 'x' que abaixa a caneta tambem desenha a celula onde ela esta
		   (e isso que o enunciado pede nos exemplos). */
		if(game->draw && (flag == 0))
		{
			/* verificacao de seguranca para nunca escrever fora da matriz
			   (os limites ja sao garantidos no switch acima) */
			if((game->i >= 0 )&& (game->i < game->height) && (game->j >= 0) && (game->j < game->width))
				game->board[game->i][game->j] = game->alive;
		}
		/* NOTA: 'flag' so e declarada a 0 uma vez, antes do ciclo, e nunca
		   volta a 0. Isto nao causa problema nos testes porque o unico
		   caractere invalido costuma ser o '\n' no FIM da entrada (echo). */
	}
}

/*
** count_neighbors
** Conta quantos dos 8 vizinhos da celula (i, j) estao vivos.
** Vizinhos fora do tabuleiro sao considerados mortos (regra do enunciado),
** por isso basta ignora-los.
*/
int count_neighbors(t_game* game, int i, int j)
{
	int count = 0;

	/* di (deslocamento na linha) e dj (deslocamento na coluna) variam
	   entre -1, 0 e 1. Isto percorre o quadrado 3x3 centrado na celula:
	       (-1,-1) (-1,0) (-1,1)
	       ( 0,-1) ( 0,0) ( 0,1)
	       ( 1,-1) ( 1,0) ( 1,1)                                        */
	for(int di = -1; di < 2; di++)
	{
		for(int dj = -1; dj < 2; dj++)
		{
			/* (0,0) e a propria celula, nao conta como vizinha */
			if((di == 0) && (dj == 0))
				continue;

			int ni = i + di;    /* linha do vizinho  */
			int nj = j + dj;    /* coluna do vizinho */

			/* so olha para o vizinho se ele estiver dentro do tabuleiro;
			   senao acederiamos memoria que nao e nossa */
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
** Calcula UMA geracao. A nova geracao e escrita num tabuleiro temporario
** (temp) e so no fim substitui o original. Isto e essencial: se alterassemos
** o tabuleiro enquanto o percorremos, as celulas ja atualizadas
** estragariam a contagem de vizinhos das celulas seguintes.
**
** Regras de Conway:
**   - viva  com 2 ou 3 vizinhos vivos -> continua viva
**   - viva  com outro numero          -> morre
**   - morta com exatamente 3 vizinhos -> nasce
**   - morta com outro numero          -> continua morta
** Retorna 0 em sucesso, -1 se a alocacao falhar.
*/
int play(t_game* game)
{
	/* Aloca o tabuleiro temporario, igual ao de init_game
	   (vetor de linhas + cada linha). */
	char** temp = (char**)malloc((game->height) * sizeof(char *));
	if(!temp)
		return(-1);
	for(int i = 0; i < game->height; i++)
	{
		temp[i] = (char *)malloc((game->width) * sizeof(char));
		if(!(temp[i]))
			return(-1);
	}

	/* Percorre todas as celulas do tabuleiro ATUAL e escreve o novo
	   estado de cada uma em temp. */
	for(int i = 0; i < game->height; i++)
	{
		for(int j = 0; j < game->width; j++)
		{
			int neighbors = count_neighbors(game, i, j);

			if(game->board[i][j] == game->alive) {
				/* celula viva: sobrevive com 2 ou 3 vizinhos */
				if(neighbors == 2 || neighbors == 3) {
					temp[i][j] = game->alive;
				}
				else
					temp[i][j] = game->dead;   /* morre: solidao ou superpopulacao */
			}
			else {
				/* celula morta: nasce com exatamente 3 vizinhos */
				if(neighbors == 3) {
					temp[i][j] = game->alive;
				}
				else
					temp[i][j] = game->dead;
			}
		}
	}

	/* Libera o tabuleiro antigo e passa a usar o novo.
	   Assim, o ponteiro board sempre aponta para a geracao mais recente. */
	free_board(game);
	game->board = temp;
	return(0);
}

/*
** print_board
** Imprime o tabuleiro, linha a linha, com putchar (a unica funcao de
** saida permitida no exame). Cada linha termina com '\n'.
*/
void print_board(t_game* game)
{
	for(int i = 0; i < game->height; i++)
	{
		for(int j = 0; j < game->width; j++)
		{
			putchar(game->board[i][j]);   /* 'O' ou ' ' */
		}
		putchar('\n');                    /* fim da linha */
	}
}

/*
** free_board
** Liberta a memoria do tabuleiro, pela ordem inversa da alocacao:
** primeiro cada linha, depois o vetor de ponteiros.
*/
void free_board(t_game* game)
{
	if(game->board)                       /* so se o tabuleiro existir */
	{
		for(int i = 0; i < game->height; i++)
		{
			if(game->board[i])            /* so se a linha existir */
				free(game->board[i]);
		}
		free(game->board);
	}
}

/*
** main
** Valida os argumentos e chama as etapas pela ordem certa.
*/
int main(int argc, char* argv[])
{
	/* argc conta o nome do programa + 3 argumentos = 4. Se for diferente,
	   o uso esta errado e o programa termina com codigo 1 (erro). */
	if(argc != 4)
		return (1);

	t_game game;     /* o estado do jogo vive na stack do main */

	/* 1. cria o tabuleiro vazio */
	if(init_game(&game, argv) == -1)
		return(1);

	/* 2. le os comandos do stdin e desenha a configuracao inicial */
	fill_board(&game);

	/* 3. simula as geracoes pedidas. Com iterations = 0 o ciclo nao
	   executa nenhuma vez e o programa imprime so o desenho inicial. */
	for(int i = 0; i < game.iterations; i++) {
		if(play(&game) == -1) {       /* falta de memoria: aborta */
			free_board(&game);
			return(1);
		}
	}

	/* 4. imprime o resultado e 5. liberta a memoria */
	print_board(&game);
	free_board(&game);

	return (0);
}
