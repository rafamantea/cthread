

CC=gcc

all: objetos executavel

objetos:
	$(CC) -Wall -c processador.c trabalho_parte2.c

executavel:
	$(CC) -Wall bin/support.o processador.o trabalho_parte2.o

delete_objetos:
	rm *.o

delete_executavel:
	rm a.out

delete_barulho:
	rm *~

clean: delete_objetos delete_executavel delete_barulho


