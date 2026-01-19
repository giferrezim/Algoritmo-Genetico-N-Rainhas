#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> // Para memcmp
#include "main.h"
#include "populacao.h"
#include "fitness.h"
#include "ordenacao.h"
#include "operadoresDeReproducao.h"
#include "selecao.h"


void atualizaPopulacao(int **proximaPopulacao, int **populacaoAtual){
    int i, j;

    for (i=0; i<TAMANHOPOPULACAO; i++){
        for (j=0; j<TAMANHOTABULEIRO; j++)
            populacaoAtual[i][j] = proximaPopulacao[i][j];
    }
}

/*
    Evolui a população até que a quantidade de evoluções sejam alcançadas ou até que uma solução ótima seja encontrada
*/
int evoluiPopulacao(int rodada, int **individuosTorneio, int **pai, int *fitnessTorneio, int **tabuleiro, int **proximaPopulacao, int encontrouSolucao, int **populacaoAtual, int *fitnessDaPopulacao){
    int indiceInicio = 0;
    int *indice = &indiceInicio;

    encontrouSolucao = fitness(tabuleiro, fitnessDaPopulacao, encontrouSolucao, populacaoAtual);
    ordenaPopulacao(populacaoAtual, fitnessDaPopulacao);
    elitismo(indice, proximaPopulacao, populacaoAtual);
    do{
        switch (TIPODESELECAO){
            case 1: selecaoAleatoria(pai, populacaoAtual);
                    break;
            case 2: selecaoRoleta(pai, fitnessDaPopulacao, populacaoAtual);
                    break;
            case 3: selecaoTorneio(individuosTorneio, pai, fitnessTorneio, populacaoAtual, fitnessDaPopulacao);
                    break;
            case 4: selecaoTorneioDosDissimilares(individuosTorneio, pai, fitnessTorneio, populacaoAtual, fitnessDaPopulacao);
                    break;
        }

        switch (TIPODECRUZAMENTO){
            case 1: cruzamentoUmPonto(indice, pai, proximaPopulacao);
                    break;
            case 2: cruzamentoDoisPontos(indice, pai, proximaPopulacao);
                    break;
        }

        mutacao(indice, proximaPopulacao);

    } while (indiceInicio < TAMANHOPOPULACAO);

    atualizaPopulacao(proximaPopulacao, populacaoAtual);
    encontrouSolucao = fitness(tabuleiro, fitnessDaPopulacao, encontrouSolucao, populacaoAtual);
    ordenaPopulacao(populacaoAtual, fitnessDaPopulacao);

    return encontrouSolucao;
}

/*
    Inicializa  a população inicial com uma rainha em cada coluna, mas a linha é colocada de forma aleatória
*/

// Função para verificar se um indivíduo já existe na população
bool existeDuplicata(int **populacao, int individuo[], int tamanhoAtual) {
    for (int i = 0; i < tamanhoAtual; i++) {
        if (memcmp(populacao[i], individuo, sizeof(int) * TAMANHOTABULEIRO) == 0) {
            return true; // Encontrou duplicata
        }
    }
    return false; // Não encontrou duplicata
}

void inicializaPopulacao(int **populacaoAtual) {
    int individuo[TAMANHOTABULEIRO];
    int tamanhoAtual = 0;

    while (tamanhoAtual < TAMANHOPOPULACAO) {
        // Gera um indivíduo aleatório
        for (int j = 0; j < TAMANHOTABULEIRO; j++) {
            individuo[j] = rand() % TAMANHOTABULEIRO;
        }

        // Verifica duplicata
        if (!existeDuplicata(populacaoAtual, individuo, tamanhoAtual)) {
            // Adiciona à população
            for (int j = 0; j < TAMANHOTABULEIRO; j++) {
                populacaoAtual[tamanhoAtual][j] = individuo[j];
            }
            tamanhoAtual++;
        }
        // Caso seja duplicata, o while gera outro indivíduo
    }
}
