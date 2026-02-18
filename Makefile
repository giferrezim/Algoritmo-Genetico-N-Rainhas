# Makefile raiz do projeto N-Rainhas

# Caminhos
BACKEND_DIR = backend
FRONTEND_DIR = frontend

# Alvos padrão
all: setup

# Setup completo
setup: backend frontend-install
	@echo ""
	@echo "===================================="
	@echo "Setup completo!"
	@echo "Para iniciar o projeto:"
	@echo "mingw32-make start - Inicia backend e frontend"
	@echo "===================================="

# Iniciar o projeto (backend + frontend)
start: backend
	@echo "Iniciando frontend..."
	@cd $(FRONTEND_DIR) && node src/index.js

# Backend
backend:
	@echo "Compilando backend..."
	$(MAKE) -C $(BACKEND_DIR)

backend-run:
	@echo "Executando backend..."
	$(MAKE) -C $(BACKEND_DIR) run

backend-clean:
	@echo "Limpando backend..."
	$(MAKE) -C $(BACKEND_DIR) clean

backend-rebuild:
	@echo "Recompilando backend..."
	$(MAKE) -C $(BACKEND_DIR) rebuild

# Frontend
frontend-install:
	@echo "Instalando dependências do frontend..."
	$(MAKE) -C $(FRONTEND_DIR) install

frontend-run:
	@echo "Executando frontend..."
	$(MAKE) -C $(FRONTEND_DIR) run

frontend-dev:
	@echo "Executando frontend em modo dev..."
	$(MAKE) -C $(FRONTEND_DIR) dev

frontend-clean:
	@echo "Limpando frontend..."
	$(MAKE) -C $(FRONTEND_DIR) clean

frontend-reinstall:
	@echo "Reinstalando dependências do frontend..."
	$(MAKE) -C $(FRONTEND_DIR) reinstall

# Comandos combinados
run: backend-run frontend-run

dev: backend-run frontend-dev

clean: backend-clean frontend-clean

rebuild: backend-rebuild frontend-reinstall

# Ajuda
help:
	@echo "Comandos disponíveis na raiz:"
	@echo ""
	@echo "SETUP INICIAL (após clonar do GitHub):"
	@echo "  make setup                 - Compila backend e instala dependências frontend"
	@echo "  make start                 - Inicia o projeto completo"
	@echo ""
	@echo "BACKEND:"
	@echo "  make backend               - Compila backend"
	@echo "  make backend-run           - Executa backend"
	@echo "  make backend-clean         - Limpa backend"
	@echo "  make backend-rebuild       - Recompila backend"
	@echo ""
	@echo "FRONTEND:"
	@echo "  make frontend-install      - Instala dependências frontend"
	@echo "  make frontend-run          - Executa frontend"
	@echo "  make frontend-dev          - Executa frontend em modo dev"
	@echo "  make frontend-clean        - Limpa frontend"
	@echo "  make frontend-reinstall    - Reinstala dependências frontend"
	@echo ""
	@echo "COMANDOS COMBINADOS:"
	@echo "  make run                   - Roda backend e frontend"
	@echo "  make dev                   - Roda backend e frontend em dev"
	@echo "  make clean                 - Limpa backend e frontend"
	@echo "  make rebuild               - Recompila backend e reinstala frontend"

.PHONY: all setup start backend backend-run backend-clean backend-rebuild \
        frontend-install frontend-run frontend-dev frontend-clean frontend-reinstall \
        run dev clean rebuild help
