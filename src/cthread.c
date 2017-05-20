#include "../include/support.h"
#include "../include/processador.h"
#include "../include/cdata.h"
#include "../include/cthread.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ucontext.h>

#define VERY_HIGH 0
#define HIGH 1
#define MEDIUM 2
#define LOW 3

//Filas de apto
PFILA2 ready_very_high;
PFILA2 ready_high;
PFILA2 ready_medium;
PFILA2 ready_low;

//Fila bloqueados
PFILA2 blocked;

int ccreate (void *(*start)(void *), void *arg, int prio) {
	
}

int csetprio(int tid, int prio) {
	
}

int csignal() {
	
}

int cyield(void) {
	
}

int cjoin(int tid) {
	
}

int csem_init (csem_t *sem, int count) {
	
}

int cwait (csem_t *sem) {
	
}

int csignal (csem_t *sem) {
	
}

int cidentify (char *name, int size){
    if(name == NULL){
        name = malloc(sizeof(char) * size);
    }

    if(size <= 0){
        perror("[ERROR] [cidentify] tamanho negativo\n");
        return -1;
    }

    char students[] = "Rafael Pinheiro Amantea - 228433\n Mauricio Carmelo - xxxxxx\n";
    int i = 0;

    while (i < size && i < sizeof(students)){
        name[i] = students[i];
        i++;
    }

    return 0;
}
