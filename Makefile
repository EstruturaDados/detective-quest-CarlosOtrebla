# ============================================
#   Makefile — Detective Quest
# ============================================

# Compilador e flags
CC      = gcc
FLAGS   = -Wall -Wextra -std=c17

# Nome do executável gerado
TARGET  = detective

# Lista de todos os arquivos .c do projeto
SRCS    = main.c mapa.c pistas.c

# Regra padrão: compila tudo
all:
	$(CC) $(SRCS) -o $(TARGET) $(FLAGS)

# Remove o executável gerado
clean:
	del $(TARGET).exe
