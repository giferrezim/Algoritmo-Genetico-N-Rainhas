# Makefile para API N-Rainhas

# Instalar dependências
install:
	npm install

# Executar o servidor
run:
	node src/index.js

# Executar o servidor em modo desenvolvimento (com nodemon, se instalado)
dev:
	npx nodemon src/index.js

# Limpar node_modules
clean:
	if exist node_modules rmdir /s /q node_modules || rm -rf node_modules

# Reinstalar dependências
reinstall: clean install

# Ajuda
help:
	@echo "Comandos disponíveis:"
	@echo "  make install    - Instala as dependências"
	@echo "  make run        - Inicia o servidor"
	@echo "  make dev        - Inicia o servidor com hot-reload"
	@echo "  make clean      - Remove node_modules"
	@echo "  make reinstall  - Reinstala as dependências"

.PHONY: install run dev clean reinstall help
