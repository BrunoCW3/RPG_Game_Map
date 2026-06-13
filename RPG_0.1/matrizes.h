#ifndef matrizes_h
#define matrizes_h

// Usamos 'extern' para avisar aos outros arquivos que essas variáveis existem,
// mas elas serão criadas de verdade e alocadas apenas no matrizes.c
extern char matriz_vis[16][16];                                                 
extern int matriz_under[16][16];   
extern int matriz_selecionados[16][16];                                            
extern int rows;        
extern int columns; 
extern int pos_inicialx;
extern int pos_inicialy;
extern int pos_atualx;
extern int pos_atualy;

void gera_matriz_under();
void gera_matriz_vis(int p, int q);
void movimenta_personagem(int *pos_atualx, int *pos_atualy, int *rows, int *columns);
void revela(int *pos_atualx, int *pos_atualy);

#endif