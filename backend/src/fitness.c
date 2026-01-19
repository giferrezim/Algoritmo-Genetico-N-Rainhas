#include "main.h"
#include <stdio.h>
#include "fitness.h"
#include <stdlib.h>

/*
    Conta o número total de colisões (pares de rainhas que se atacam)
*/
int contarColisoes(int *individuo) {
    int i, j, colisoes = 0;
    
    for (i = 0; i < TAMANHOTABULEIRO; i++) {
        for (j = i + 1; j < TAMANHOTABULEIRO; j++) {
            // Mesma linha
            if (individuo[i] == individuo[j]) {
                colisoes++;
            }
            // Mesma diagonal
            if (abs(individuo[i] - individuo[j]) == abs(i - j)) {
                colisoes++;
            }
        }
    }
    
    return colisoes;
}

int fitnessIndividuo(int *individuo) {
    int i, linha, rainhasSemConflito = 0;

    // aloca vetores e já inicializa em 0
    int *linhas = (int*) calloc(TAMANHOTABULEIRO, sizeof(int));
    int *diag1  = (int*) calloc(2*TAMANHOTABULEIRO, sizeof(int));
    int *diag2  = (int*) calloc(2*TAMANHOTABULEIRO, sizeof(int));

    // Primeiro passa: marcar posições ocupadas
    for (i = 0; i < TAMANHOTABULEIRO; i++) {
        linha = individuo[i];
        linhas[linha]++;
        diag1[i+linha]++;
        diag2[i-linha+TAMANHOTABULEIRO]++;
    }

    // Segunda passa: contar rainhas sem conflito
    for (i = 0; i < TAMANHOTABULEIRO; i++) {
        linha = individuo[i];
        // Uma rainha não tem conflito se ela é a única em sua linha e diagonais
        if (linhas[linha] == 1 && 
            diag1[i+linha] == 1 && 
            diag2[i-linha+TAMANHOTABULEIRO] == 1) {
            rainhasSemConflito++;
        }
    }

    // Liberar a memória
    free(linhas);
    free(diag1);
    free(diag2);

    // Retorna o número de rainhas sem conflito
    return rainhasSemConflito;
}


int fitness(int **tabuleiro , int *fitnessDaPopulacao , int encontrouSolucao , int ** populacaoAtual){
    int i;
    for (i=0; i<TAMANHOPOPULACAO; i++){
        // Calcula o fitness direto a partir do vetor do indivíduo
        fitnessDaPopulacao[i] = fitnessIndividuo(populacaoAtual[i]);

        // Se fitness == TAMANHOTABULEIRO, encontrou solução perfeita
        if (fitnessDaPopulacao[i] == TAMANHOTABULEIRO)
            encontrouSolucao = 1;
    }
    return encontrouSolucao;
}

/*
    Posiciona as rainhas no tabuleiro
    0 indica posicao vazia
    1 indica Rainhas
*/
void posicionaRainhas(int individuo, int **tabuleiro, int **populacaoAtual){
    int i, j;
    int linhaDaRainha;

    for (i=0; i<TAMANHOTABULEIRO; i++){
        for (j=0; j<TAMANHOTABULEIRO; j++){
            linhaDaRainha = populacaoAtual[individuo][j];
            if (i == (linhaDaRainha))
                tabuleiro[i][j] = 1;
            else
                tabuleiro[i][j] = 0;
        }
    }
}
