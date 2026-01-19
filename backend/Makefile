# Makefile para o projeto N-Rainhas

CC = gcc
CFLAGS = -Wall -Wextra -O2
INCLUDES = -I include

# Diretórios
SRC_DIR = src
APP_DIR = apps
INC_DIR = include

# Arquivos fonte
SRCS = $(APP_DIR)/main.c \
       $(SRC_DIR)/fitness.c \
       $(SRC_DIR)/operadoresDeReproducao.c \
       $(SRC_DIR)/ordenacao.c \
       $(SRC_DIR)/populacao.c \
       $(SRC_DIR)/print.c \
       $(SRC_DIR)/selecao.c

# Nome do executável
TARGET = nrainhas.exe

# Regra padrão
all: $(TARGET)

# Compilar o executável
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCS) -o $(TARGET)

# Compilar e executar
run: $(TARGET)
	.\$(TARGET)

# Limpar arquivos gerados
clean:
	del /Q $(TARGET) 2>nul || rm -f $(TARGET)
	del /Q dadosNRainhas.txt 2>nul || rm -f dadosNRainhas.txt

# Limpar apenas o executável
clean-exe:
	del /Q $(TARGET) 2>nul || rm -f $(TARGET)

# Recompilar do zero
rebuild: clean all

.PHONY: all run clean clean-exe rebuild
