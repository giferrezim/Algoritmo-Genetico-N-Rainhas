# Interface e Servidor de Aplicação  

Este módulo implementa a interface do sistema por meio de um servidor de aplicação desenvolvido em Node.js, responsável por:
- Receber, via requisições HTTP, os parâmetros de configuração do algoritmo genético definidos pelo usuário;  
- Executar o backend computacional implementado em linguagem C (nrainhas.exe);  
- Processar e disponibilizar os resultados da execução em formato estruturado (JSON);  
- Servir a interface web (HTML, CSS e JavaScript) destinada à interação com o usuário e à visualização dos resultados.  

## Pré-requisitos

- [Node.js](https://nodejs.org/) (versão 18 ou superior)
- Executável `nrainhas.exe` (algoritmo genético compilado)

## Instalação

1. Navegue até a pasta do frontend:
```bash
cd frontend
```

2. Instale as dependências:
```bash
npm install
```

**Os caminhos são configurados automaticamente!** O servidor localiza o executável `nrainhas.exe` na pasta `../backend/` de forma relativa.

## Execução

```bash
node src/index.js
```

Ou usando o Makefile:

```bash
mingw32-make run
```

## Acessar a Interface

O servidor iniciará na porta `3003` (ou na porta definida pela variável de ambiente `PORT`).  
Acesse `http://localhost:3003/` no navegador para visualizar a interface web.

## Parâmetros Configuráveis

A interface permite configurar os seguintes parâmetros do algoritmo genético:

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

## Autoria

Desenvolvido por Giovana Vilela Ferrezim  
Orientação: Dra. Christiane Regina Soares Brasil  
Instituição: Universidade Federal de Uberlândia  
Ano: 2026
