# Algoritmo Genético para o Problema das N-Rainhas

Solução do problema das N-Rainhas por meio de um Algoritmo Genético implementado em linguagem C.

## Descrição

Este projeto implementa um algoritmo genético para resolver o problema clássico das N-Rainhas, onde o objetivo é posicionar N rainhas em um tabuleiro NxN de forma que nenhuma rainha ataque outra. O algoritmo utiliza técnicas de seleção por torneio, cruzamento, mutação e elitismo para evoluir a população e encontrar soluções ótimas.

## Pré-requisitos

- GCC (MinGW ou MSYS2 no Windows)

## Estrutura de Arquivos

```
backend/                          # Núcleo computacional: algoritmo genético em C
├── apps/main.c                   # Programa principal
├── src/                          # Implementações
│   ├── fitness.c                 # Cálculo de fitness
│   ├── populacao.c               # Gerenciamento da população
│   ├── selecao.c                 # Métodos de seleção
│   ├── operadoresDeReproducao.c  # Crossover e mutação
│   ├── ordenacao.c               # Algoritmos de ordenação
│   └── print.c                   # Saída de dados
├── include/                      # Cabeçalhos (.h)
└── Makefile                      # Build do backend
```

## Execução

Após compilar, use o Makefile para compilar e executar diretamente. No Windows, use:

```bash
mingw32-make run
```

Em sistemas Linux ou com Make instalado, use:

```bash
make run
```

## Parâmetros Configuráveis

O programa solicitará os seguintes parâmetros:

1. **Tamanho do tabuleiro (N)**: Número de rainhas e dimensão do tabuleiro
2. **Tamanho da população**: Número de indivíduos na população
3. **Tipo da seleção**:
    - 1: Aleatória (seleção randômica)
    - 2: Roleta (probabilidade proporcional ao fitness)
    - 3: Torneio (competição entre indivíduos)
    - 4: Torneio dos dissimilares (favorece diversidade)
4. **Tamanho do torneio**: Número de competidores (usado apenas para seleção tipo 3 e 4)
5. **Taxa de elitismo**: Porcentagem de quantos melhores indivíduos passam diretamente para próxima geração
6. **Taxa de mutação**: Probabilidade de mutação
7. **Tipo de crossover**: 
    - 1: Crossover de 1 ponto
    - 2: Crossover de 2 pontos
8. **Número máximo de gerações**: Limite de iterações do algoritmo

## Exemplo de Uso (Entrada Interativa)

```
Digite o tamanho do tabuleiro: 8
Digite o tamanho da populacao: 100
Digite o tipo de selecao (1- Aleatoria, 2- Roleta, 3- Torneio, 4- Dissimilares): 3
Digite a quantidade de individuos do torneio: 2
Digite a taxa de elitismo: 0.1
Digite a taxa de mutacao: 0.05
Digite o tipo de cruzamento (1- Cruzamento de um ponto, 2- Cruzamento de dois pontos): 1
Digite o numero maximo de rodadas: 50
```

## Função de Fitness

A função de fitness calcula o número de rainhas que não estão envolvidas em nenhum conflito (linha ou diagonais). O valor máximo de fitness é N, quando todas as rainhas estão posicionadas sem ataques.

## Arquivo de Saída

O programa gera o arquivo `dadosNRainhas.txt` contendo:
- População final
- Valores de fitness de cada indivíduo
- Melhor fitness encontrado
- Informações sobre as gerações do algoritmo
- Média e desvio padrão da população
- Tempo de execução em milissegundos

## Autoria

Desenvolvido por Giovana Vilela Ferrezim  
Orientação: Dra. Christiane Regina Soares Brasil  
Instituição: Universidade Federal de Uberlândia  
Ano: 2026
