#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrizes.h"

/* ---- Definição das variáveis globais ---- */
int  mat_logic[ROWS][COLS];
int  mat_vis  [ROWS][COLS];
char mat_icon [ROWS][COLS];

int player_row = ROWS - 1;
int player_col = 0;

int player_hp     = 100;
int player_max_hp = 100;
int player_atk    = 2;
int player_def    = 0;

int explored_count = 0;
int generation     = 1;

/* ------------------------------------------------------------------ */
void init_matrices(void)
{
    int r, c;

    for (r = 0; r < ROWS; r++) {
        for (c = 0; c < COLS; c++) {
            if (r == ROWS-1 && c == 0) {
                mat_logic[r][c] = CELL_SAFE;
            } else {
                double v = sin((r * 12.9898 + c * 78.233 + generation * 47.1) * 43758.5453);
                int n = (int)fabs(floor(v * 10000)) % 100;
                if      (n < 70) mat_logic[r][c] = CELL_SAFE;
                else if (n < 85) mat_logic[r][c] = CELL_ENEMY;
                else             mat_logic[r][c] = CELL_CHEST;
            }
            mat_vis [r][c] = VIS_HIDDEN;
            mat_icon[r][c] = ' ';
        }
    }

    player_row = ROWS - 1;
    player_col = 0;
    explored_count = 0;
}

/* ------------------------------------------------------------------ */
void draw_board(void)
{
    int r, c;

    printf("\n     a  b  c  d  e  f  g  h\n");
    printf("    -------------------------\n");

    for (r = 0; r < ROWS; r++) {
        printf(" %d |", ROWS - r);
        for (c = 0; c < COLS; c++) {
            if (r == player_row && c == player_col) {
                printf(" @ ");
            } else {
                switch (mat_vis[r][c]) {
                    case VIS_HIDDEN:
                        printf(" . ");
                        break;
                    case VIS_EXPLORED:
                        printf("[%c]", mat_icon[r][c]);
                        break;
                    case VIS_FLED:
                        printf(" ? ");
                        break;
                }
            }
        }
        printf("\n");
    }

    printf("\n  HP:%d/%d  ATK:%d  DEF:%d  Casas:%d/64  Floresta:#%d\n",
           player_hp, player_max_hp, player_atk, player_def,
           explored_count, generation);
    printf("  [setas] mover  [Enter] revelar  [f] fugir  [q] sair\n\n");
}
