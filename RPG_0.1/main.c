#include <stdio.h>
#include <stdlib.h>
#include "matrizes.h"

int main()
{
    gera_matriz_under();
    gera_matriz_vis(0, 0);

    printf("Voce acaba de pisar em um territorio perigoso ! Cada passo dado daqui para frente pode signficar triunfo ou morte.\n");
    printf("Escolha bem seus proximos passos e reze para chegar vivo ate a saida...\n");

    while(1){
        // Passando corretamente os endereços das variáveis globais
        movimenta_personagem(&pos_atualx, &pos_atualy, &rows, &columns);
    }
    
    system("pause");
    return 0;
}