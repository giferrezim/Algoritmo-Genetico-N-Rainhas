# Sistema Computacional para o Problema das N-Rainhas

Este repositório apresenta o sistema computacional desenvolvido no âmbito de um projeto de Iniciação Científica, cujo objetivo foi aprimorar a pesquisa de Ribeiro por meio da reformulação do Algoritmo Genético aplicado ao Problema das N-Rainhas. As melhorias propostas incluem a redução do custo computacional, a inclusão de uma busca local que testa trocas alternativas e mantém a melhor solução encontrada, além do desenvolvimento de uma interface web interativa que permite ao usuário definir os parâmetros do algoritmo genético e visualizar as soluções obtidas.

Também é disponibilizada uma tabela comparativa de resultados experimentais, contendo médias e desvios padrão do número de gerações até a convergência para diferentes instâncias do problema, permitindo analisar o desempenho do método proposto em relação à implementação original de Ribeiro.

O repositório é organizado de forma modular, incluindo:
- **Backend:** núcleo computacional implementado em linguagem C, responsável pela execução do algoritmo genético para a resolução do Problema das N-Rainhas.
- **Frontend:** camada responsável pela interação com o usuário, composta por um servidor de aplicação desenvolvido em Node.js que realiza a comunicação com o núcleo computacional e por uma interface web que permite definir parâmetros do algoritmo genético e visualizar as soluções obtidas.

## Pré-requisitos

- **Windows** com MinGW/MSYS2 (GCC)
- **Node.js** (v14 ou superior)
- **Make** (mingw32-make)

## Setup Inicial (Após Clonar do GitHub)

```bash
# Setup automático - compila backend e instala dependências
mingw32-make setup

# Inicia o servidor
mingw32-make start
```

**Não é necessário mudar nenhum caminho ou configuração!** Todos os caminhos são relativos e funcionam automaticamente.

## Acessar a Interface

O servidor iniciará na porta `3003` (ou na porta definida pela variável de ambiente `PORT`).  
Acesse `http://localhost:3003/` no navegador para visualizar a interface web.

## Estrutura do Projeto

```
N-Rainhas/
├── backend/                 # Núcleo computacional: algoritmo genético em C
│   ├── apps/                # Aplicação principal (main.c)
│   ├── src/                 # Implementação das funções do algoritmo
│   ├── include/             # Arquivos de cabeçalho (.h)
│   ├── Makefile             # Build do backend
│   └── nrainhas.exe         # Executável gerado
├── frontend/                # Servidor de aplicação em Node.js
│   ├── src/                 # Código-fonte do servidor (API REST)
│   ├── public/              # Interface web (HTML, CSS e JavaScript)
│   ├── Makefile             # Build do frontend
│   └── package.json         # Dependências do Node.js
└── Makefile                 # Orquestrador de build do projeto
```

## Comandos Make Disponíveis

| Comando              | Descrição                              |
|----------------------|----------------------------------------|
| `mingw32-make setup` | Compila backend e instala dependências |
| `mingw32-make start` | Inicia o projeto completo              |
| `mingw32-make help`  | Mostra todos os comandos disponíveis   |

## Documentação Detalhada

- Ver [backend/README.md](backend/README.md) para detalhes do algoritmo genético.
- Ver [frontend/README.md](frontend/README.md) para detalhes do servidor Node.js e da interface web.

## Autoria

Desenvolvido por Giovana Vilela Ferrezim  
Orientação: Dra. Christiane Regina Soares Brasil  
Instituição: Universidade Federal de Uberlândia  
Ano: 2026
