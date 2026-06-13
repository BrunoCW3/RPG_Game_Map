#include <stdio.h>
#include <stdlib.h>
#include "matrizes.h"
#include <conio.h>

void movimenta_personagem(int *pos_atualx, int *pos_atualy, int *rows, int *columns)
{
    int tecla = getch();

    if (tecla == 224)
    {
        tecla = getch();
        
        // Limpa a tela antes de desenhar o novo movimento
        system("cls"); 

        switch(tecla)
        {
            case 72:
                // cima: diminui a linha (Y)
                if((*pos_atualy) != 0)
                {
                gera_matriz_vis(*pos_atualx, *pos_atualy - 1);
                }
                else
                {
                gera_matriz_vis(*pos_atualx, *pos_atualy);
                }
                break;

            case 80:
                // baixo: aumenta a linha (Y)
                if((*pos_atualy) != (*rows)-1)
                {
                gera_matriz_vis(*pos_atualx, *pos_atualy + 1);
                }
                else
                {
                gera_matriz_vis(*pos_atualx, *pos_atualy);
                }
                break;

            case 75:
                // esquerda: diminui a coluna (X)
                if((*pos_atualx) != 0)
                {
                gera_matriz_vis(*pos_atualx - 1, *pos_atualy);
                }
                else
                {
                gera_matriz_vis(*pos_atualx, *pos_atualy);
                }
                break;

            case 77:
                // direita: aumenta a coluna (X)
                if((*pos_atualx) != (*columns-1))
                {
                gera_matriz_vis(*pos_atualx + 1, *pos_atualy);
                }
                else
                {
                gera_matriz_vis(*pos_atualx, *pos_atualy);
                }
                break;
            

        }
    }
    else
    if((tecla == 13))
    {
        revela(pos_atualx, pos_atualy);

    }

}