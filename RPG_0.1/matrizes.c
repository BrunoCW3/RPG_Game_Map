#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrizes.h"
#include <math.h>

// As variáveis são criadas e inicializadas de verdade AQUI:
char matriz_vis[16][16];                                                 
int matriz_under[16][16];
int matriz_selecionados[16][16] = {0};                                               
int rows = (sizeof(matriz_under)) / (sizeof(matriz_under[0]));        
int columns = (sizeof(matriz_under[0]))/(sizeof(matriz_under[0][0])); 
int pos_inicialx = 0;
int pos_inicialy = 0;
int pos_atualx = 0;
int pos_atualy = 0;

void gera_matriz_under()
{   
    int x = 0, y = 0;
    

    while(y != rows){
        for(x=0; x < columns; x++){
            
            
            double valor_pseudo = sin(x * 12.9898 + y * 78.233) * 43758.5453;
            
            
            int numero_final = (int)fabs(floor(valor_pseudo));
            
            
            matriz_under[y][x] = (numero_final % 3) + 1;                                  
        }
        y++;
    }
}

void gera_matriz_vis(int p, int q){
    int i, j;
    int a = 0, b = 0;
    while(b != rows)
    {
        
        for(a=0; a < columns; a++)
        {
            
            if(matriz_selecionados[b][a] == 0)
            {
                matriz_vis[b][a] = 'X';
            }    
            else
            {
                matriz_vis[b][a] = '0' + matriz_selecionados[b][a];
            }                              
        }
        b++;
    }
        
    
    matriz_vis[q][p] = 'O'; // q é Y (linha), p é X (coluna)
    pos_atualx = p;
    pos_atualy = q;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < columns; j++) {
            printf("%c ", matriz_vis[i][j]);
        }
        printf("\n");
    }
}