# Sistema Computacional para o Problema das N-Rainhas

Este projeto implementa um sistema para a resolução do **Problema das N-Rainhas** utilizando um **Algoritmo Genético**.  

O repositório é organizado de forma modular, incluindo:

**Backend**: núcleo computacional implementado em linguagem C.  
**Servidor de aplicação**: desenvolvido em Node.js, responsável pela comunicação entre o núcleo computacional e a interface web.  
**Frontend**: interface web para interação com o usuário e visualização dos resultados.  

O projeto foi desenvolvido no contexto de uma **Iniciação Científica**, com foco em **algoritmos evolutivos** e **problemas de otimização combinatória**.

---

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

## Estrutura do Projeto

```
N-Rainhas/
├── backend/             # Algoritmo genético em C
│   ├── apps/            # Aplicação principal (main.c)
│   ├── src/             # Implementação das funções
│   ├── include/         # Arquivos de cabeçalho (.h)
│   ├── Makefile         # Build do backend
│   └── nrainhas.exe     # Executável gerado
├── frontend/            # API REST em Node.js
│   ├── src/             # Código fonte da API RESTful
│   ├── public/          # Interface HTML
│   ├── Makefile         # Build do frontend
│   └── package.json     # Dependências Node.js
└── Makefile             # Orquestrador raiz
```

## Uso Rápido

### Iniciar o Servidor

```bash
mingw32-make start
```

O servidor estará disponível em `http://localhost:3003`

### Acessar a Interface

Abra o navegador em: `http://localhost:3003`

### Testar Diretamente

```
http://localhost:3003/run?n=8&populationSize=100&tournamentSize=5&elitismRate=0.1&mutationRate=0.01&selectionType=1&crossoverType=1&maxRounds=1000
```

## Comandos Make Disponíveis

| Comando              | Descrição                              |
|----------------------|----------------------------------------|
| `mingw32-make setup` | Compila backend e instala dependências |
| `mingw32-make start` | Inicia o projeto completo              |
| `mingw32-make help`  | Mostra todos os comandos               |

Para ver todos os comandos disponíveis, execute:
```bash
mingw32-make help
```

## Documentação Detalhada

- Ver [backend/README.md](backend/README.md) para detalhes do algoritmo genético.
- Ver [frontend/README.md](frontend/README.md) para detalhes do servidor de aplicação e da interface web.

## Autoria

Desenvolvido por Giovana Vilela Ferrezim  
Orientação: Dra. Christiane Regina Soares Brasil  
Instituição: Universidade Federal de Uberlândia  
Ano: 2026
