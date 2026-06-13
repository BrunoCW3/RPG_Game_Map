#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrizes.h"

void revela(int *pos_atualx, int *pos_atualy){
    // Salva o valor lógico em formato de coordenadas [Y][X]
    matriz_selecionados[*pos_atualy][*pos_atualx] = matriz_under[*pos_atualy][*pos_atualx];
    
    system("cls");
    
    // Manda desenhar a matriz. Ela vai ler a matriz_selecionados e colocar o caractere certo
    gera_matriz_vis(*pos_atualx, *pos_atualy);
}