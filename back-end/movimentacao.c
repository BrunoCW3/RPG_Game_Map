#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "matrizes.h"

/* conio.h (MinGW/MSVC Windows):
   getch() retorna 0 ou 224 quando uma tecla especial é pressionada,
   e uma segunda chamada retorna o código da tecla:
     72 = cima, 80 = baixo, 75 = esquerda, 77 = direita  */

void movement_loop(void)
{
    while (1) {
        system("cls");
        draw_board();

        int ch = getch();

        /* Teclas especiais (setas): prefixo 0 ou 224 */
        if (ch == 0 || ch == 224) {
            int arrow = getch();
            int nr = player_row;
            int nc = player_col;

            switch (arrow) {
                case 72: nr--; break;   /* cima     */
                case 80: nr++; break;   /* baixo    */
                case 75: nc--; break;   /* esquerda */
                case 77: nc++; break;   /* direita  */
            }

            /* Limites */
            if (nr < 0)      nr = 0;
            if (nr >= ROWS)  nr = ROWS - 1;
            if (nc < 0)      nc = 0;
            if (nc >= COLS)  nc = COLS - 1;

            player_row = nr;
            player_col = nc;
            continue;
        }

        /* Enter: revela a casa atual */
        if (ch == '\r' || ch == '\n') {
            system("cls");
            draw_board();
            do_reveal(player_row, player_col);
            printf("  [ENTER para continuar]");
            getch();
            continue;
        }

        /* f: fugir da casa atual (se tiver inimigo ativo) */
        if (ch == 'f' || ch == 'F') {
            if (mat_vis[player_row][player_col] == VIS_FLED ||
                mat_logic[player_row][player_col] == CELL_ENEMY) {
                try_flee(player_row, player_col);
                printf("  [ENTER para continuar]");
                getch();
            }
            continue;
        }

        /* q: sair */
        if (ch == 'q' || ch == 'Q') {
            printf("\n  Ate logo, aventureiro!\n\n");
            exit(0);
        }
    }
}
