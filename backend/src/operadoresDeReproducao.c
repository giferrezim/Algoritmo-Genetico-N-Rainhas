#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "main.h"
#include "operadoresDeReproducao.h"
#include "fitness.h"


/*
    São selecionados dois pontos de corte diferentes entre si de maneira aleatória nos individuos pais
    Recombina os dois pais gerando um novo filho
    Repara o filho para garantir que seja uma permutação válida (sem linhas repetidas)
    Adiciona o filho na próxima geração e atualiza *indice
*/
void cruzamentoDoisPontos(int *indice, int **pai, int **proximaPopulacao){
    int i;
    int corte1, corte2;
    int filho[TAMANHOTABULEIRO];

    do{
        corte1 = rand() % TAMANHOTABULEIRO+1;
        corte2 = rand() % TAMANHOTABULEIRO+1;
    } while (corte1 == corte2 || (corte1 == TAMANHOTABULEIRO || corte2 == TAMANHOTABULEIRO) );

    if (corte1 > corte2){
        for (i=0; i<=corte2; i++)
            filho[i] = pai[0][i];

        for (i=corte2+1; i<=corte1; i++)
            filho[i] = pai[1][i];

        for (i=corte1+1; i<TAMANHOTABULEIRO; i++)
            filho[i] = pai[0][i];
    }
    else {
        for (i=0; i<corte1; i++)
            filho[i] = pai[0][i];

        for (i=corte1; i<corte2; i++)
            filho[i] = pai[1][i];

        for (i=corte2; i<TAMANHOTABULEIRO; i++)
            filho[i] = pai[0][i];
    }

    // Repara o filho para ser uma permutação válida
    // identifica valores duplicados e substitui pelos valores ausentes
    int presentes[TAMANHOTABULEIRO];
    for (i = 0; i < TAMANHOTABULEIRO; i++) presentes[i] = 0;
    for (i = 0; i < TAMANHOTABULEIRO; i++) presentes[filho[i]] = 1;

    // Coleta os valores ausentes
    int ausentes[TAMANHOTABULEIRO];
    int numAusentes = 0;
    for (i = 0; i < TAMANHOTABULEIRO; i++)
        if (!presentes[i]) ausentes[numAusentes++] = i;

    // Substitui duplicatas pelos valores ausentes
    int aIdx = 0;
    int visto[TAMANHOTABULEIRO];
    for (i = 0; i < TAMANHOTABULEIRO; i++) visto[i] = 0;
    for (i = 0; i < TAMANHOTABULEIRO; i++) {
        if (visto[filho[i]])
            filho[i] = ausentes[aIdx++];
        else
            visto[filho[i]] = 1;
    }

    // Adiciona o filho na população
    for (i=0; i<TAMANHOTABULEIRO; i++)
        proximaPopulacao[*indice][i] = filho[i];

    *indice = (*indice)+1;
}

/*
    Seleciona aleatoriamente um ponto de corte nos individuos pais
    Recombina os dois pais gerando um novo filho
    Repara o filho para garantir que seja uma permutação válida 
    Adiciona o filho gerado na próxima geração e atualiza *indice
*/
void cruzamentoUmPonto(int *indice, int **pai, int **proximaPopulacao){
    int i;
    int corte;
    int filho[TAMANHOTABULEIRO];

    do{
        corte = rand()% TAMANHOTABULEIRO+1;
    } while (corte == TAMANHOTABULEIRO);

    for (i=0; i<corte; i++)
        filho[i] = pai[0][i];

    for (i=corte; i<TAMANHOTABULEIRO; i++)
        filho[i] = pai[1][i];

    // Repara o filho para ser uma permutação válida
    // identifica valores duplicados e substitui pelos valores ausentes
    int presentes[TAMANHOTABULEIRO];
    for (i = 0; i < TAMANHOTABULEIRO; i++) presentes[i] = 0;
    for (i = 0; i < TAMANHOTABULEIRO; i++) presentes[filho[i]] = 1;

    int ausentes[TAMANHOTABULEIRO];
    int numAusentes = 0;
    for (i = 0; i < TAMANHOTABULEIRO; i++)
        if (!presentes[i]) ausentes[numAusentes++] = i;

    int aIdx = 0;
    int visto[TAMANHOTABULEIRO];
    for (i = 0; i < TAMANHOTABULEIRO; i++) visto[i] = 0;
    for (i = 0; i < TAMANHOTABULEIRO; i++) {
        if (visto[filho[i]])
            filho[i] = ausentes[aIdx++];
        else
            visto[filho[i]] = 1;
    }

    // Adiciona o filho na populacao
    for (i=0; i<TAMANHOTABULEIRO; i++)
        proximaPopulacao[*indice][i] = filho[i];

    *indice = (*indice)+1;
}

/*
    Define a partir da TAXAMUTACAO se haverá ou não mutação
    Caso ocorra, sorteia aleatoriamente entre 1 e N/2 swaps a realizar
    Cada swap troca duas posições distintas, preservando a permutação
*/
void mutacao(int *indice, int **proximaPopulacao){
    double chance = (double)rand() / RAND_MAX;

    if (chance < TAXAMUTACAO) {
        int maxSwaps = TAMANHOTABULEIRO / 2;
        if (maxSwaps < 1) maxSwaps = 1;
        int quantidadeSwaps = (rand() % maxSwaps) + 1;

        for (int s = 0; s < quantidadeSwaps; s++) {
            int pos1 = rand() % TAMANHOTABULEIRO;
            int pos2;
            do {
                pos2 = rand() % TAMANHOTABULEIRO;
            } while (pos1 == pos2);

            int temp = proximaPopulacao[(*indice-1)][pos1];
            proximaPopulacao[(*indice-1)][pos1] = proximaPopulacao[(*indice-1)][pos2];
            proximaPopulacao[(*indice-1)][pos2] = temp;
        }
    }
}

/*
    Testa algumas trocas (swaps) aleatórias no indivíduo e mantém a melhor encontrada, caso melhore o fitness
    Sempre é aplicada
*/
void buscaLocal(int *indice, int **proximaPopulacao){
    int i;
    int fitnessAntigo = fitnessIndividuo(proximaPopulacao[(*indice-1)]);
    int melhorFitness = fitnessAntigo;
    int melhorIndividuo[TAMANHOTABULEIRO];

    // Cópia do indivíduo original
    for (i = 0; i < TAMANHOTABULEIRO; i++)
        melhorIndividuo[i] = proximaPopulacao[(*indice-1)][i];

    // Testa algumas trocas alternativas
    for (int t = 0; t < 3; t++) {
        int temp[TAMANHOTABULEIRO];
        for (i = 0; i < TAMANHOTABULEIRO; i++)
            temp[i] = proximaPopulacao[(*indice-1)][i];

        // Escolhe duas posições aleatórias diferentes para trocar
        int pos1 = rand() % TAMANHOTABULEIRO;
        int pos2;
        do {
            pos2 = rand() % TAMANHOTABULEIRO;
        } while (pos1 == pos2);

        // Troca os valores nas duas colunas
        int temp_val = temp[pos1];
        temp[pos1] = temp[pos2];
        temp[pos2] = temp_val;

        int fit = fitnessIndividuo(temp);

        // Mantém a melhor troca encontrada
        if (fit > melhorFitness) {
            melhorFitness = fit;
            for (i = 0; i < TAMANHOTABULEIRO; i++)
                melhorIndividuo[i] = temp[i];
        }
    }

    // Atualiza o indivíduo na população com o melhor resultado
    for (i = 0; i < TAMANHOTABULEIRO; i++)
        proximaPopulacao[(*indice-1)][i] = melhorIndividuo[i];
}




