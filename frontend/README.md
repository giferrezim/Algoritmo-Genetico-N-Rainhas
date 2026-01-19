# Interface e API N-Rainhas

Este módulo implementa a interface do sistema por meio de uma API REST em Node.js. A API é responsável por:
- Receber os parâmetros do algoritmo genético via requisições HTTP
- Executar o backend computacional implementado em C (`nrainhas.exe`)
- Processar e retornar os resultados da execução em formato JSON
- Servir a interface HTML para interação com o usuário


## Pré-requisitos

- [Node.js](https://nodejs.org/) (versão 18 ou superior)
- Executável `nrainhas.exe` (algoritmo genético compilado)

## Instalação

1. Clone o repositório:
```bash
git clone <seu-repositorio>
cd API
```

2. Instale as dependências:
```bash
npm install
```

**✨ Os caminhos são configurados automaticamente!** O servidor localiza o executável `nrainhas.exe` na pasta `../backend/` de forma relativa.

## Execução

```bash
node src/index.js
```

Ou usando o Makefile:

```bash
mingw32-make run
```

O servidor iniciará na porta `3003` (ou na porta definida pela variável de ambiente `PORT`).

## Endpoints Disponíveis

### GET `/`
Retorna a interface HTML principal do sistema.

**Resposta**: Arquivo HTML com interface para configuração e visualização dos resultados.

### GET `/run`
Executa o algoritmo genético com os parâmetros especificados.

**Resposta**: JSON contendo os dados da execução (população por fitness, por geração e tempo de execução).

### Parâmetros do Endpoint `/run`

O endpoint `/run` recebe, via query string, os principais parâmetros do algoritmo genético, como tamanho do tabuleiro, população, método de seleção, taxas de elitismo e mutação, tipo de crossover e número máximo de gerações.

| Parâmetro        | Tipo  | Descrição                          |
|------------------|-------|------------------------------------|
| `n`              | int   | Tamanho do tabuleiro (mínimo 4)    |
| `populationSize` | int   | Tamanho da população               |
| `tournamentSize` | int   | Tamanho do torneio                 |
| `elitismRate`    | float | Taxa de elitismo (0 a 1)           |
| `mutationRate`   | float | Taxa de mutação (0 a 1)            |
| `selectionType`  | int   | Tipo de seleção (1–4)              |
| `crossoverType`  | int   | Tipo de cruzamento (1 ou 2)        |
| `maxRounds`      | int   | Número máximo de gerações          |

## Exemplo de chamada

```http
GET http://localhost:3003/run?n=8&populationSize=100&tournamentSize=2&elitismRate=0.1&mutationRate=0.05&selectionType=3&crossoverType=1&maxRounds=100
```

**Forma relativa**
```
GET /run?n=8&populationSize=100&tournamentSize=2&elitismRate=0.1&mutationRate=0.05&selectionType=3&crossoverType=1&maxRounds=100
```

## Autoria

Desenvolvido por Giovana Vilela Ferrezim  
Orientação: Dra. Christiane Regina Soares Brasil  
Instituição: Universidade Federal de Uberlândia  
Ano: 2026
