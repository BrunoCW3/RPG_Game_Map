#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include "matrizes.h"

static const char *enemy_names[] = {
    "Goblin", "Bugbear", "Kobold", "Hobgoblin",
    "Gnoll",  "Troll",   "Ogre",   "Basilisk"
};
#define NUM_ENEMIES (int)(sizeof(enemy_names)/sizeof(enemy_names[0]))

/* ---- RNG sem rand() ---- */
static int rng_seed = 7;
static int rng_range(int lo, int hi)
{
    rng_seed = (rng_seed * 1103515245 + 12345) & 0x7fffffff;
    int r = rng_seed % (hi - lo + 1);
    return lo + (r < 0 ? -r : r);
}

static void press_enter(void)
{
    printf("  [ENTER para continuar]");
    getch();
}

/* ------------------------------------------------------------------ */
void check_victory(void)
{
    if (explored_count < ROWS * COLS) return;

    system("cls");
    draw_board();
    printf("\n  *** PARABENS! Voce explorou toda a floresta! ***\n");
    printf("  Deseja ir para outra floresta? [s/n]: ");
    int ch = getch();
    printf("%c\n", ch);

    if (ch == 's' || ch == 'S') {
        generation++;
        init_matrices();
        printf("\n  -> Floresta #%d. Boa sorte!\n\n", generation);
        press_enter();
    } else {
        printf("\n  O explorador descansa... fim de jogo.\n");
        press_enter();
        exit(0);
    }
}

/* ------------------------------------------------------------------ */
void do_chest(int row, int col)
{
    printf("\n  [BAU] Voce encontrou um bau!\n");

    int roll = rng_range(0, 99);

    if (roll < 60) {
        int item = rng_range(0, 2);
        if      (item == 0) { player_atk += 2; printf("  -> Espada de Madeira (+2 ATK)\n"); }
        else if (item == 1) { player_def += 5; printf("  -> Armadura Velha    (+5 DEF)\n"); }
        else                { player_def += 4; printf("  -> Escudo de Madeira (+4 DEF)\n"); }
    } else if (roll < 85) {
        int item = rng_range(0, 2);
        if      (item == 0) { player_atk += 7;  printf("  -> Espada Velha      (+7 ATK)\n"); }
        else if (item == 1) { player_def += 7;  printf("  -> Escudo de Soldado (+7 DEF)\n"); }
        else {
            player_atk += 10; player_max_hp -= 10;
            if (player_hp > player_max_hp) player_hp = player_max_hp;
            printf("  -> Espada Amaldic.  (+10 ATK / -10 HP max)\n");
        }
    } else {
        int item = rng_range(0, 1);
        if (item == 0) { player_atk += 20; printf("  -> Espada do Anjo   (+20 ATK) [RARO]\n"); }
        else           { player_def += 20; printf("  -> Armadura do Anjo (+20 DEF) [RARO]\n"); }
    }

    mat_logic[row][col] = CELL_SAFE;
    mat_vis  [row][col] = VIS_EXPLORED;
    mat_icon [row][col] = 'C';
    explored_count++;
    press_enter();
}

/* ------------------------------------------------------------------ */
void do_combat(int row, int col)
{
    const char *name = enemy_names[rng_range(0, NUM_ENEMIES-1)];
    int e_hp  = player_max_hp + rng_range(-5, 5); if (e_hp  < 5) e_hp  = 5;
    int e_atk = player_atk    + rng_range(-5, 5); if (e_atk < 1) e_atk = 1;
    int e_def = player_def    + rng_range(-5, 5); if (e_def < 0) e_def = 0;

    printf("\n  [COMBATE] Um %s aparece!\n", name);
    printf("  Inimigo -> HP:%d  ATK:%d  DEF:%d\n", e_hp, e_atk, e_def);
    press_enter();

    int consecutive_def = 0;
    int player_defending = 0;

    while (player_hp > 0 && e_hp > 0) {
        system("cls");
        draw_board();
        printf("\n  --- COMBATE: %s ---\n", name);
        printf("  Voce  HP:%d/%d  ATK:%d  DEF:%d\n", player_hp, player_max_hp, player_atk, player_def);
        printf("  %s   HP:%d  ATK:%d  DEF:%d\n\n", name, e_hp, e_atk, e_def);
        printf("  Atacar [y] / Defender [n] / Fugir [f]: ");

        int ch = getch();
        printf("%c\n", ch);

        /* Fugir */
        if (ch == 'f' || ch == 'F') {
            try_flee(row, col);
            return;
        }

        if (ch == 'y' || ch == 'Y') {
            consecutive_def = 0;
            player_defending = 0;
            int dmg = player_atk;
            e_hp -= dmg;
            printf("  -> Voce causou %d de dano! (%s HP: %d)\n", dmg, name, e_hp < 0 ? 0 : e_hp);

            if (e_hp <= 0) {
                printf("\n  >> Vitoria! %s foi derrotado!\n", name);
                mat_logic[row][col] = CELL_SAFE;
                mat_icon [row][col] = 'G';
                if (mat_vis[row][col] != VIS_FLED) {
                    explored_count++;
                }
                mat_vis[row][col] = VIS_EXPLORED;
                press_enter();
                check_victory();
                return;
            }
        } else {
            /* Defender */
            consecutive_def++;
            player_defending = 1;
            printf("  -> Voce se defende... (%d/3)\n", consecutive_def);
            if (consecutive_def >= 3) {
                printf("  -> 3 defesas seguidas! Fuga automatica!\n");
                press_enter();
                try_flee(row, col);
                return;
            }
        }

        /* Turno do inimigo */
        if (rng_range(0, 1) == 0) {
            int dmg = e_atk;
            if (player_defending) dmg -= player_def;
            if (dmg < 0) dmg = 0;
            player_hp -= dmg;
            printf("  <- %s atacou! Voce sofreu %d de dano. (Seu HP: %d)\n",
                   name, dmg, player_hp < 0 ? 0 : player_hp);
            player_defending = 0;

            if (player_hp <= 0) {
                printf("\n  *** GAME OVER *** Voce foi derrotado por %s!\n", name);
                printf("  Floresta #%d  |  ATK:%d  DEF:%d\n", generation, player_atk, player_def);
                press_enter();
                exit(0);
            }
        } else {
            printf("  <- %s se defende.\n", name);
        }

        press_enter();
    }
}

/* ------------------------------------------------------------------ */
void try_flee(int row, int col)
{
    int chance = 100 - (explored_count * 100 / (ROWS * COLS));
    int roll   = rng_range(0, 99);

    if (roll < chance) {
        printf("\n  -> Fuga bem-sucedida!\n");
        printf("     Casa marcada com '?' — volte para terminar o combate.\n");
        if (mat_vis[row][col] != VIS_FLED) {
            mat_vis  [row][col] = VIS_FLED;
            mat_logic[row][col] = CELL_ENEMY;
            explored_count++;
        }
    } else {
        printf("\n  -> Fuga falhou! O combate continua...\n");
        press_enter();
        do_combat(row, col);
        return;
    }
    press_enter();
}

/* ------------------------------------------------------------------ */
void do_reveal(int row, int col)
{
    if (mat_vis[row][col] == VIS_EXPLORED) {
        printf("  Essa casa ja foi explorada.\n");
        return;
    }

    /* Casa onde o jogador fugiu — retoma combate */
    if (mat_vis[row][col] == VIS_FLED) {
        printf("\n  [!] Uma criatura ainda esta aqui!\n");
        printf("  Combater? [y/n]: ");
        int ch = getch();
        printf("%c\n", ch);
        if (ch == 'y' || ch == 'Y') {
            explored_count--;   /* vai ser recontado ao derrotar */
            do_combat(row, col);
        }
        return;
    }

    /* Casa nova */
    int type = mat_logic[row][col];

    if (type == CELL_ENEMY || type == CELL_CHEST) {
        char coord_col = 'a' + col;
        int  coord_row = ROWS - row;
        printf("\n  [!] Um ruido vem de %c%d! Prosseguir? [y/n]: ",
               coord_col, coord_row);
        int ch = getch();
        printf("%c\n", ch);
        if (ch != 'y' && ch != 'Y') {
            printf("  Voce recuou.\n");
            return;
        }
        /* Mimetismo 50% */
        if (rng_range(0, 1) == 0) {
            type = (type == CELL_ENEMY) ? CELL_CHEST : CELL_ENEMY;
        }
    }

    player_row = row;
    player_col = col;

    if (type == CELL_SAFE) {
        mat_vis [row][col] = VIS_EXPLORED;
        mat_icon[row][col] = ' ';
        explored_count++;
        printf("  Caminho seguro.\n");
        check_victory();
    } else if (type == CELL_CHEST) {
        mat_vis[row][col] = VIS_EXPLORED;
        do_chest(row, col);
    } else {
        do_combat(row, col);
    }
}
