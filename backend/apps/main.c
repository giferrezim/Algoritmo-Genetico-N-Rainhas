#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <windows.h>
#include "main.h"
#include "fitness.h"
#include "operadoresDeReproducao.h"
#include "ordenacao.h"
#include "populacao.h"
#include "print.h"
#include "selecao.h"

int TAMANHOTABULEIRO = 0;
int TAMANHOPOPULACAO = 0;
int QUANTIDADEINDIVIDUOSPORTORNEIO = 0;
double TAXAMUTACAO = 0;
double TAXAELITISMO = 0; 
int TIPODESELECAO = 0;
int TIPODECRUZAMENTO = 0;

// Função auxiliar para encontrar o melhor indivíduo com um dado fitness
int buscarMelhorIndividuo(int **populacaoAtual, int *fitnessDaPopulacao, int fitnessAlvo, int *colisoes) {
    int melhorIndice = -1;
    int menorColisoes = 999999;
    
    for (int k = 0; k < TAMANHOPOPULACAO; k++) {
        if (fitnessDaPopulacao[k] == fitnessAlvo) {
            int col = contarColisoes(populacaoAtual[k]);
            if (col < menorColisoes) {
                menorColisoes = col;
                melhorIndice = k;
            }
        }
    }
    
    if (colisoes != NULL) {
        *colisoes = menorColisoes;
    }
    return melhorIndice;
}

int main(){
    setbuf(stdout, NULL);  // Desabilita buffering do stdout
    setbuf(stdin, NULL);   // Desabilita buffering do stdin
    
    // Timer de alta precisão
    LARGE_INTEGER frequency, begin_real, agora_real;
    QueryPerformanceFrequency(&frequency);

    int i, j;
    int *fitnessTorneio, *fitnessDaPopulacao;
    int **individuosTorneio, **pai, **tabuleiro, **proximaPopulacao, **populacaoAtual;
    int encontrouSolucao = 0;
    FILE *arquivo;
    MelhorPorFitness *melhoresPorFitness;
    MelhorPorFitness *progressoPorGeracao;
    int numProgressos = 0;
    int melhorFitnessGlobalAtual = -1;
    double tempo_real_ultimo_ms = 0.0;

    printf("Digite o tamanho do tabuleiro: ");
    scanf("%d", &TAMANHOTABULEIRO);

    printf("Digite o tamanho da populacao: ");
    scanf("%d", &TAMANHOPOPULACAO);

    printf("Digite o tipo de selecao (1- Aleatoria, 2- Roleta, 3- Torneio, 4- Dissimilares): ");
    scanf("%d", &TIPODESELECAO);

    if(TIPODESELECAO == 3 || TIPODESELECAO == 4){
        printf("Digite a quantidade de individuos do torneio: ");
        scanf("%d", &QUANTIDADEINDIVIDUOSPORTORNEIO);
    }

    printf("Digite a taxa de elitismo: ");
    scanf("%lf", &TAXAELITISMO);

    printf("Digite a taxa de mutacao: ");
    scanf("%lf", &TAXAMUTACAO);

    printf("Digite o tipo de cruzamento (1- Cruzamento de um ponto, 2- Cruzamento de dois pontos): ");
    scanf("%d", &TIPODECRUZAMENTO);

    int maxRodadas;
    printf("Digite o numero maximo de rodadas: ");
    scanf("%d", &maxRodadas);

    // Iniciar contagem do tempo APÓS todas as entradas do usuário
    QueryPerformanceCounter(&begin_real);

    // Inicializar array para rastrear melhores indivíduos por fitness
    melhoresPorFitness = (MelhorPorFitness*) malloc((TAMANHOTABULEIRO + 1) * sizeof(MelhorPorFitness));
    for (i = 0; i <= TAMANHOTABULEIRO; i++) {
        melhoresPorFitness[i].individuo = NULL;
        melhoresPorFitness[i].fitness = i;
        melhoresPorFitness[i].colisoes = 0;
        melhoresPorFitness[i].geracao = 0;
        melhoresPorFitness[i].tempo = 0.0;
        melhoresPorFitness[i].encontrado = 0;
    }    
    // Inicializar array para rastrear progressos por geração (máximo = maxRodadas)
    progressoPorGeracao = (MelhorPorFitness*) malloc(maxRodadas * sizeof(MelhorPorFitness));
    for (j = 0; j < maxRodadas; j++) {
        progressoPorGeracao[j].individuo = NULL;
        progressoPorGeracao[j].fitness = 0;
        progressoPorGeracao[j].colisoes = 0;
        progressoPorGeracao[j].geracao = 0;
        progressoPorGeracao[j].tempo = 0.0;
        progressoPorGeracao[j].encontrado = 0;
    }
    populacaoAtual = (int **) malloc(TAMANHOPOPULACAO * sizeof(int *));
    for (i=0; i<TAMANHOPOPULACAO; i++)
        populacaoAtual[i] = (int *)malloc(TAMANHOTABULEIRO * sizeof(int));

    proximaPopulacao = (int **) malloc(TAMANHOPOPULACAO * sizeof(int *));
    for (i=0; i<TAMANHOPOPULACAO; i++)
        proximaPopulacao[i] = (int *)malloc(TAMANHOTABULEIRO * sizeof(int));

    individuosTorneio = (int **) malloc(QUANTIDADEINDIVIDUOSPORTORNEIO * sizeof(int *));
    for (i=0; i<QUANTIDADEINDIVIDUOSPORTORNEIO; i++)
        individuosTorneio[i] = (int *)malloc(TAMANHOTABULEIRO * sizeof(int));

    pai = (int **) malloc(2 * sizeof(int *));
    for (i=0; i<2; i++)
        pai[i] = (int *)malloc(TAMANHOTABULEIRO * sizeof(int));

    tabuleiro = (int **) malloc(TAMANHOTABULEIRO * sizeof(int *));
    for (i=0; i<TAMANHOTABULEIRO; i++)
        tabuleiro[i] = (int *)malloc(TAMANHOTABULEIRO * sizeof(int));

    fitnessDaPopulacao = (int*) malloc(TAMANHOPOPULACAO * sizeof(int));
    fitnessTorneio = (int*) malloc(QUANTIDADEINDIVIDUOSPORTORNEIO * sizeof(int));

    // Gerar a população inicial
    inicializaPopulacao(populacaoAtual);

    // Loop evolutivo
    for (i = 0; i < maxRodadas && !encontrouSolucao; i++) {
        // Evoluir população
        encontrouSolucao = evoluiPopulacao(i, individuosTorneio, pai, fitnessTorneio, tabuleiro, proximaPopulacao, encontrouSolucao, populacaoAtual, fitnessDaPopulacao);

        // Atualizar tempo APÓS a evolução (alta precisão)
        QueryPerformanceCounter(&agora_real);
        double tempo_real_ms = (double)(agora_real.QuadPart - begin_real.QuadPart) * 1000.0 / frequency.QuadPart;

        // Encontrar o melhor fitness da geração
        int maiorFitnessDaGeracao = 0;
        for (j = 0; j < TAMANHOPOPULACAO; j++) {
            if (fitnessDaPopulacao[j] > maiorFitnessDaGeracao) {
                maiorFitnessDaGeracao = fitnessDaPopulacao[j];
            }
        }

        // Registrar todos os fitness encontrados pela primeira vez nesta geração
        for (j = 0; j < TAMANHOPOPULACAO; j++) {
            int fitnessAtual = fitnessDaPopulacao[j];
            
            // Se este fitness ainda não foi registrado, registrar agora
            if (!melhoresPorFitness[fitnessAtual].encontrado) {
                int menorColisoes;
                int melhorIndice = buscarMelhorIndividuo(populacaoAtual, fitnessDaPopulacao, fitnessAtual, &menorColisoes);
                
                if (melhorIndice >= 0) {
                    // Alocar e copiar indivíduo
                    if (melhoresPorFitness[fitnessAtual].individuo == NULL) {
                        melhoresPorFitness[fitnessAtual].individuo = (int*) malloc(TAMANHOTABULEIRO * sizeof(int));
                    }
                    for (int k = 0; k < TAMANHOTABULEIRO; k++) {
                        melhoresPorFitness[fitnessAtual].individuo[k] = populacaoAtual[melhorIndice][k];
                    }
                    melhoresPorFitness[fitnessAtual].colisoes = menorColisoes;
                    melhoresPorFitness[fitnessAtual].geracao = i + 1;
                    melhoresPorFitness[fitnessAtual].tempo = tempo_real_ms / 1000.0;
                    melhoresPorFitness[fitnessAtual].encontrado = 1;
                }
            }
        }
        
        // Registrar progresso por geração (apenas se o melhor fitness global melhorou)
        if (maiorFitnessDaGeracao > melhorFitnessGlobalAtual) {
            melhorFitnessGlobalAtual = maiorFitnessDaGeracao;
            
            int menorColisoes;
            int melhorIndice = buscarMelhorIndividuo(populacaoAtual, fitnessDaPopulacao, maiorFitnessDaGeracao, &menorColisoes);
            
            if (melhorIndice >= 0) {
                progressoPorGeracao[numProgressos].individuo = (int*) malloc(TAMANHOTABULEIRO * sizeof(int));
                for (int k = 0; k < TAMANHOTABULEIRO; k++) {
                    progressoPorGeracao[numProgressos].individuo[k] = populacaoAtual[melhorIndice][k];
                }
                progressoPorGeracao[numProgressos].fitness = maiorFitnessDaGeracao;
                progressoPorGeracao[numProgressos].colisoes = menorColisoes;
                progressoPorGeracao[numProgressos].geracao = i + 1;
                progressoPorGeracao[numProgressos].tempo = tempo_real_ms / 1000.0;
                progressoPorGeracao[numProgressos].encontrado = 1;
                tempo_real_ultimo_ms = tempo_real_ms;
                numProgressos++;
            }
        }

        // Imprimir progresso a cada 100 rodadas ou na última
        if ((i + 1) % 100 == 0 || encontrouSolucao) {
            printf("Rodada %d - Melhor fitness: %d\n", i + 1, melhorFitnessGlobalAtual);
        }
    }

    // Mostrar população no console
    printf("\n");
    mostraPopulacao(populacaoAtual, fitnessDaPopulacao);
    
    // Abrir arquivo e sobrescrever com dados da nova execução
    arquivo = fopen("dadosNRainhas.txt", "w");
    if (arquivo == NULL) {
        printf("ERRO AO ABRIR ARQUIVO PARA SALVAR DADOS!\n");
        return 1;
    }

    // Escrever população final e fitness no arquivo
    fprintf(arquivo, "- Populacao Final -\t - Fitness -\n");
    for (j = 0; j < TAMANHOPOPULACAO; j++) {
        for (int k = 0; k < TAMANHOTABULEIRO; k++) {
            fprintf(arquivo, "%d ", populacaoAtual[j][k]);
        }
        fprintf(arquivo, "\t%d\n", fitnessDaPopulacao[j]);
    }
    
    // Calcular média e desvio padrão
    double soma = 0.0;
    for (j = 0; j < TAMANHOPOPULACAO; j++) {
        soma += fitnessDaPopulacao[j];
    }
    double media = soma / TAMANHOPOPULACAO;
    
    double somaQuadrados = 0.0;
    for (j = 0; j < TAMANHOPOPULACAO; j++) {
        double diff = fitnessDaPopulacao[j] - media;
        somaQuadrados += diff * diff;
    }
    double desvio = sqrt(somaQuadrados / TAMANHOPOPULACAO);
    
    // Encontrar maior fitness
    int maiorFitness = 0;
    for (j = 0; j < TAMANHOPOPULACAO; j++) {
        if (fitnessDaPopulacao[j] > maiorFitness) {
            maiorFitness = fitnessDaPopulacao[j];
        }
    }
    
    fprintf(arquivo, "Maior fitness\t%d\n", maiorFitness);
    fprintf(arquivo, "Media fitness\t%.2f\n", media);
    fprintf(arquivo, "Devio padrao\t%.2f\n", desvio);
    fprintf(arquivo, "Tamanho da populacao\t%d\n", TAMANHOPOPULACAO);
    fprintf(arquivo, "Tamanho do tabuleiro\t %d\n", TAMANHOTABULEIRO);
    fprintf(arquivo, "Quantidade de individuos por torneio\t %d\n", QUANTIDADEINDIVIDUOSPORTORNEIO);
    fprintf(arquivo, "Taxa de elitismo\t %.2f\n", TAXAELITISMO);
    fprintf(arquivo, "Taxa de mutacao\t %.2f\n", TAXAMUTACAO);
    fprintf(arquivo, "Tipo de selecao\t");
    if(TIPODESELECAO == 1)
        fprintf(arquivo, "Selecao aleatoria\n");
    else if(TIPODESELECAO == 2)
        fprintf(arquivo, "Selecao por roleta\n");
    else if(TIPODESELECAO == 3)
        fprintf(arquivo, "Selecao por torneio\n");
    else if(TIPODESELECAO == 4)
        fprintf(arquivo, "Selecao por torneio dos dissimilares\n");
    fprintf(arquivo, "Tipo de cruzamento\t ");
    if(TIPODECRUZAMENTO == 1)
        fprintf(arquivo, "Cruzamento de um ponto\n");
    else if(TIPODECRUZAMENTO == 2)
        fprintf(arquivo, "Cruzamento de dois pontos\n");
    fprintf(arquivo, "Rodadas\t %d\n\n", i);

    // Escrever exemplos de indivíduos por cada nível de fitness encontrado
    fprintf(arquivo, "=== INDIVIDUOS POR NIVEL DE FITNESS ===\n");
    fprintf(arquivo, "Fitness\tGeracao\tIndividuo\n");
    
    for (j = 0; j <= TAMANHOTABULEIRO; j++) {
        if (melhoresPorFitness[j].encontrado) {
            fprintf(arquivo, "%d\t%d\t", 
                melhoresPorFitness[j].fitness,
                melhoresPorFitness[j].geracao);
            
            for (int k = 0; k < TAMANHOTABULEIRO; k++) {
                fprintf(arquivo, "%d ", melhoresPorFitness[j].individuo[k]);
            }
            fprintf(arquivo, "\n");
        }
    }

    // Escrever melhores indivíduos por geração (apenas progresso até encontrar a solução)
    fprintf(arquivo, "\n=== MELHORES INDIVIDUOS POR GERACAO (APENAS PROGRESSO) ===\n");
    fprintf(arquivo, "Geracao\tFitness\tIndividuo\n");
    
    // Imprimir progressos registrados
    for (j = 0; j < numProgressos; j++) {
        fprintf(arquivo, "%d\t%d\t", 
            progressoPorGeracao[j].geracao,
            progressoPorGeracao[j].fitness);
        
        for (int k = 0; k < TAMANHOTABULEIRO; k++) {
            fprintf(arquivo, "%d ", progressoPorGeracao[j].individuo[k]);
        }
        fprintf(arquivo, "\n");
        
        // Se encontrou a solução, parar
        if (progressoPorGeracao[j].fitness == TAMANHOTABULEIRO) {
            break;
        }
    }
    
    fprintf(arquivo, "\nTempo para encontrar melhor fitness: %.0f ms (%.6f segundos)\n", tempo_real_ultimo_ms, tempo_real_ultimo_ms / 1000.0);
    
    fclose(arquivo);

    // Liberando memória dos melhores por fitness
    for (i = 0; i <= TAMANHOTABULEIRO; i++) {
        if (melhoresPorFitness[i].individuo != NULL) {
            free(melhoresPorFitness[i].individuo);
        }
    }
    free(melhoresPorFitness);

    // Liberando memória alocada
    for (i=0; i<TAMANHOPOPULACAO; i++){
        free(populacaoAtual[i]);
        free(proximaPopulacao[i]);
    }
    free(populacaoAtual);
    free(proximaPopulacao);
    for (i=0; i<QUANTIDADEINDIVIDUOSPORTORNEIO; i++)
        free(individuosTorneio[i]);
    free(individuosTorneio);
    for (i=0; i<2; i++)
        free(pai[i]);
    free(pai);
    for (i=0; i<TAMANHOTABULEIRO; i++)
        free(tabuleiro[i]);
    free(tabuleiro);
    free(fitnessDaPopulacao);
    free(fitnessTorneio);

    return 0;
}
    