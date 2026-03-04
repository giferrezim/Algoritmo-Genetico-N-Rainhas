#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
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
        buscaLocal(indice, proximaPopulacao);

    } while (indiceInicio < TAMANHOPOPULACAO);

    atualizaPopulacao(proximaPopulacao, populacaoAtual);
    encontrouSolucao = fitness(tabuleiro, fitnessDaPopulacao, encontrouSolucao, populacaoAtual);
    ordenaPopulacao(populacaoAtual, fitnessDaPopulacao);

    return encontrouSolucao;
}

/*
    Inicializa  a população inicial com permutações aleatórias de 0 a N-1
    Evitando conflitos de linha já na população inicial
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
        // Gera uma permutação aleatória
        // Garante que cada linha apareça exatamente uma vez
        // Eliminando conflitos de linha já na população inicial
        for (int j = 0; j < TAMANHOTABULEIRO; j++)
            individuo[j] = j;
        for (int j = TAMANHOTABULEIRO - 1; j > 0; j--) {
            int r = rand() % (j + 1);
            int tmp = individuo[j];
            individuo[j] = individuo[r];
            individuo[r] = tmp;
        }

        // Verifica duplicata
        if (!existeDuplicata(populacaoAtual, individuo, tamanhoAtual)) {
            for (int j = 0; j < TAMANHOTABULEIRO; j++)
                populacaoAtual[tamanhoAtual][j] = individuo[j];
            tamanhoAtual++;
        }
    }
}
