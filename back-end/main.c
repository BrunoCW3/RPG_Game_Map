#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "matrizes.h"

void movement_loop(void);

int main(void)
{
    system("cls");
    printf("  ======================================\n");
    printf("   Jogo de Exploracao RPG  --  Terminal \n");
    printf("  ======================================\n\n");
    printf("  Voce acaba de pisar em um territorio perigoso!\n");
    printf("  Cada passo pode significar triunfo ou morte.\n");
    printf("  Escolha bem seus proximos passos...\n\n");
    printf("  Legenda:\n");
    printf("    @  = voce\n");
    printf("    .  = desconhecido\n");
    printf("   [ ] = casa segura\n");
    printf("   [G] = goblin derrotado\n");
    printf("   [C] = bau aberto\n");
    printf("    ?  = inimigo ativo (voce fugiu)\n\n");
    printf("  [qualquer tecla para comecar]");
    getch();

    init_matrices();
    movement_loop();

    return 0;
}
