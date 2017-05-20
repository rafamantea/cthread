#
# Makefile ESQUELETO
#
# OBRIGATÓRIO ter uma regra "all" para geração da biblioteca e de uma
# regra "clean" para remover todos os objetos gerados.
#
# NECESSARIO adaptar este esqueleto de makefile para suas necessidades.
#  1. Cuidado com a regra "clean" para não apagar o "fila2.o"
#
# OBSERVAR que as variáveis de ambiente consideram que o Makefile está no diretótio "cthread"
#

AR=ar
CRS=crs
CC=gcc
LIB_DIR=./lib/
INC_DIR=./include/
BIN_DIR=./bin/
SRC_DIR=./src/
TST_DIR=./testes/
CFLAGS= -Wall -g -I$(INC_DIR)

all: lib

lib: cthread cdata
	ar crs $(LIB_DIR)libcthread.a $(BIN_DIR)support.o $(BIN_DIR)cdata.o $(BIN_DIR)cthread.o

cthread: $(SRC_DIR)cthread.c
	$(CC) -c $(SRC_DIR)cthread.c -Wall -o $(BIN_DIR)cthread.o -g

cdata: $(SRC_DIR)cdata.c
	$(CC) -c $(SRC_DIR)cdata.c -Wall -o $(BIN_DIR)cdata.o -g

clean:
	find $(BIN_DIR) $(LIB_DIR) -type f ! -name 'support.o' ! -name 'Makefile' -delete
