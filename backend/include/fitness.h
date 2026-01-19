#include "main.h"

int fitness(int **tabuleiro, int *fitnessDaPopulacao, int encontrouSolucao, int **populacaoAtual);
int fitnessIndividuo(int *individuo);
int contarColisoes(int *individuo);
void posicionaRainhas(int individuo, int **tabuleiro, int **populacaoAtual);
