
CC=gcc

all: objetos executavel

objetos:
	$(CC) -c processador.c trabalho_parte1.c

executavel:
	$(CC) bin/support.o processador.o trabalho_parte1.o

delete_objetos:
	rm *.o

delete_executavel:
	rm a.out

delete_barulho:
	rm *~

clean: delete_objetos delete_executavel delete_barulho



