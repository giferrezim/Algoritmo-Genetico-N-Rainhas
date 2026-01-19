#ifndef MAIN_H
#define MAIN_H

#define MAXGERACOES 10000 // parâmetro de parada

extern int TAMANHOPOPULACAO;
extern int TAMANHOTABULEIRO;
extern int QUANTIDADEINDIVIDUOSPORTORNEIO;
extern double TAXAELITISMO; 
extern double TAXAMUTACAO;
extern int TIPODESELECAO; // 1- Aleatória. 2- Roleta. 3- Torneio. 4- Torneio dos dissimilares
extern int TIPODECRUZAMENTO; // 1- Cruzamento de um ponto. 2- Cruzamento de dois ponto

// Estrutura para armazenar o melhor indivíduo de cada fitness
typedef struct {
    int *individuo;
    int fitness;
    int colisoes;
    int geracao;
    double tempo;
    int encontrado; // 0 = não encontrado, 1 = encontrado
} MelhorPorFitness;

#endif // MAIN_H

