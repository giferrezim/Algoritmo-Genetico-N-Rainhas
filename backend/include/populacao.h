#include "main.h"

void atualizaPopulacao(int **proximaPopulacao, int **populacaoAtual);
int evoluiPopulacao(int i, int **individuosTorneio, int **pai, int *fitnessTorneio, int **tabuleiro, int **proximaPopulacao, int encontrouSolucao, int **populacaoAtual, int *fitnessDaPopulacao);
void inicializaPopulacao(int **populacaoAtual);
