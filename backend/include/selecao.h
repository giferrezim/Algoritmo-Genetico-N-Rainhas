#include "main.h"

void elitismo(int*, int **proximaPopulacao, int **populacaoAtual);
void selecaoAleatoria(int **pai, int **populacaoAtual);
void selecaoRoleta(int **pai, int *fitnessDaPopulacao, int **populacaoAtual);
void selecaoTorneio(int **individuosTorneio, int **pai, int *fitnessTorneio, int **populacaoAtual, int *fitnessDaPopulacao);
void selecaoTorneioDosDissimilares(int **individuosTorneio, int **pai, int *fitnessTorneio, int **populacaoAtual, int *fitnessDaPopulacao);