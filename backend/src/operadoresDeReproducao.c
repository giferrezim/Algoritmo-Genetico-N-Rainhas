#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "main.h"
#include "operadoresDeReproducao.h"
#include "fitness.h"


/*
    São selecionados dois pontos de corte diferentes entre si de maneira aleatória nos individuos pais.
    Recombina os dois pais gerando um novo filho.
    Adiciona o filho na próxima geração.
    Retorna o indice do ultimo indivíduo da população.
*/
void cruzamentoDoisPontos(int *indice, int **pai, int **proximaPopulacao){
    int i;
    int corte1, corte2;
    int filho[TAMANHOPOPULACAO];

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

    // Adiciona o filho na popula��o
    for (i=0; i<TAMANHOTABULEIRO; i++)
        proximaPopulacao[*indice][i] = filho[i];

    *indice = (*indice)+1;
}

/*
    Seleciona aleatoriamente um ponto de corte nos individuos pais.
    Recombina os dois pais gerando um novo filho.
    Adiciona o filho gerado na próxima geração
    Retorna o indice do último indivíduo da população.
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

    // Adiciona o filho na populacao
    for (i=0; i<TAMANHOTABULEIRO; i++)
        proximaPopulacao[*indice][i] = filho[i];

    *indice = (*indice)+1;
}

/*
    Define a partir da TAXAMUTACAO se haverá ou não mutação.
    Caso a mutação ocorra, define de modo aleatório quantos pontos serão mutados (1 ou 2),
    define de modo aleatório quais os pontos de mutação e muta o individiduo filho
*/

void mutacao(int *indice, int **proximaPopulacao){
    int i;
    int fitnessAntigo = fitnessIndividuo(proximaPopulacao[(*indice-1)]);
    int melhorFitness = fitnessAntigo;
    int melhorIndividuo[TAMANHOTABULEIRO];

    // Cópia do indivíduo original
    for (i = 0; i < TAMANHOTABULEIRO; i++)
        melhorIndividuo[i] = proximaPopulacao[(*indice-1)][i];

    // Testa algumas mutações alternativas
    for (int t = 0; t < 3; t++) {
        int temp[TAMANHOTABULEIRO];
        for (i = 0; i < TAMANHOTABULEIRO; i++)
            temp[i] = proximaPopulacao[(*indice-1)][i];

        // Escolhe duas posições (colunas) aleatórias diferentes para trocar
        int pos1 = rand() % TAMANHOTABULEIRO;
        int pos2;
        do {
            pos2 = rand() % TAMANHOTABULEIRO;
        } while (pos1 == pos2);

        // Mutação: Troca os valores (linhas) nas duas colunas
        int temp_val = temp[pos1];
        temp[pos1] = temp[pos2];
        temp[pos2] = temp_val;

        int fit = fitnessIndividuo(temp);

        // Mantém a melhor mutação encontrada
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




