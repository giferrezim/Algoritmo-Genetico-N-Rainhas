#include <stdio.h>
#include <math.h>
#include "main.h"
#include "print.h"

/*
    Mostra cada indivíduo da população seguido do seu fitness.
    Mostra o indivíduo com maior fitness.
    Mostra a media de fitness da população.
    Mostra o desvio padrao do fintess dos individuos
    Salva todos esses dados em um arquivo "dadosNRainhas.xls"
*/
void mostraPopulacao(int **populacaoAtual, int *fitnessDaPopulacao){
    int i, j;

    float mediaFitness = 0;
    for (i=0; i<TAMANHOPOPULACAO; i++){
        for (j=0; j<TAMANHOTABULEIRO; j++){
            printf("%d ", populacaoAtual[i][j]);
        }
        printf("Fitness: %d\n", fitnessDaPopulacao[i]);
        mediaFitness += fitnessDaPopulacao[i];
    }

    // Calcula o desvio padrão
    mediaFitness = mediaFitness/TAMANHOPOPULACAO;
    float variacoes = 0;
    for (i=0; i<TAMANHOPOPULACAO; i++) {
        variacoes += pow((fitnessDaPopulacao[i] - mediaFitness), 2);
    }
    float sigma;
    sigma = sqrt(variacoes/TAMANHOPOPULACAO);

    printf("Maior fitness: %d\n", fitnessDaPopulacao[TAMANHOPOPULACAO-1]);
    printf("Media fitness: %f\n", mediaFitness);
    printf("Desvio padrao: %f\n", sigma);
}

/*
    Mostra na tela o tabuleiro com as rainhas posicionadas
    0 indica posição vazia
    1 indica rainha
*/
void mostraTabuleiro(int **tabuleiro){
    int i, j;

    for (i=0; i<TAMANHOTABULEIRO; i++){
        for (j=0; j<TAMANHOTABULEIRO; j++)
            printf("%d ", tabuleiro[i][j]);
        printf("\n");
    }
    printf("\n");
}
