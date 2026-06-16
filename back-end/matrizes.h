#ifndef MATRIZES_H
#define MATRIZES_H

#define ROWS    8
#define COLS    8

/* Valores da matriz lógica */
#define CELL_SAFE    0
#define CELL_ENEMY   1
#define CELL_CHEST   2

/* Estado visual da célula */
#define VIS_HIDDEN   0   /* não revelada */
#define VIS_EXPLORED 1   /* revelada e vazia / baú aberto / inimigo morto */
#define VIS_FLED     2   /* inimigo ativo mas jogador fugiu */

/* ---- Matrizes globais ---- */
extern int  mat_logic[ROWS][COLS];   /* 0=seguro 1=inimigo 2=baú        */
extern int  mat_vis  [ROWS][COLS];   /* VIS_HIDDEN / EXPLORED / FLED     */
extern char mat_icon [ROWS][COLS];   /* ' ' 'G' 'C' '?' para fugido      */

/* ---- Posição do jogador ---- */
extern int player_row;
extern int player_col;

/* ---- Atributos do jogador ---- */
extern int player_hp;
extern int player_max_hp;
extern int player_atk;
extern int player_def;

/* ---- Contadores ---- */
extern int explored_count;   /* casas reveladas (inclui fugas) */
extern int generation;       /* floresta atual */

/* ---- Protótipos ---- */
void init_matrices(void);
void draw_board(void);

void do_reveal(int row, int col);
void do_chest(int row, int col);
void do_combat(int row, int col);
void try_flee(int row, int col);

void check_victory(void);

#endif
